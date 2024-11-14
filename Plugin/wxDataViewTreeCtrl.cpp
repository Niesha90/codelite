#include "wxDataViewTreeCtrl.hpp"

#include <algorithm>
#include <wx/sizer.h>
#include <wx/wupdlock.h>

namespace
{
wxTreeItemId to_tree_item(const wxDataViewItem& item)
{
    wxTreeItemId tree_item(item.m_pItem);
    return tree_item;
}
wxDataViewItem from_tree_item(const wxTreeItemId& item)
{
    wxDataViewItem dv_item(item.m_pItem);
    return dv_item;
}
} // namespace

wxTreeItemId wxTreeCtrlDataViewBaseCookie::Next()
{
    auto item = m_children[m_index];
    ++m_index;
    return to_tree_item(item);
}

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxControl(parent, wxID_ANY)
{
    m_impl = new wxDataViewTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                    wxDV_MULTIPLE | wxDV_NO_HEADER | wxDV_ROW_LINES | wxBORDER_NONE);

#if defined(__WXMSW__)
    wxColour wincolour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    if (wxSystemSettings::GetAppearance().IsDark()) {
        m_impl->SetAlternateRowColour(wincolour.ChangeLightness(102));
    } else {
        m_impl->SetAlternateRowColour(wincolour.ChangeLightness(98));
    }
#endif

    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(m_impl, wxSizerFlags(1).Expand());
    m_impl->Bind(wxEVT_DATAVIEW_ITEM_EXPANDED, &wxTreeCtrlDataViewBase::OnItemExpandedInternal, this);
    m_impl->Bind(wxEVT_DATAVIEW_ITEM_EXPANDING, &wxTreeCtrlDataViewBase::OnItemExpandingInternal, this);
    m_impl->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &wxTreeCtrlDataViewBase::OnItemActivatedInternal, this);
    m_impl->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &wxTreeCtrlDataViewBase::OnItemContextMenuInternal, this);

    // Disable item editing
    m_impl->Bind(wxEVT_DATAVIEW_ITEM_START_EDITING, [](wxDataViewEvent& event) { event.Veto(); });
}

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase() {}
wxTreeCtrlDataViewBase::~wxTreeCtrlDataViewBase()
{
    if (m_impl) {
        m_impl->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDED, &wxTreeCtrlDataViewBase::OnItemExpandedInternal, this);
        m_impl->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDING, &wxTreeCtrlDataViewBase::OnItemExpandingInternal, this);
        m_impl->Unbind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &wxTreeCtrlDataViewBase::OnItemActivatedInternal, this);
        m_impl->Unbind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &wxTreeCtrlDataViewBase::OnItemContextMenuInternal, this);
    }
}

void wxTreeCtrlDataViewBase::SetBitmaps(BitmapLoader::Vec_t* bitmaps)
{
    wxDataViewTreeCtrl::Images images;
    images.reserve(bitmaps->size());
    images.insert(images.end(), bitmaps->begin(), bitmaps->end());

    m_impl->SetImages(images);
}

wxTreeItemId wxTreeCtrlDataViewBase::AddRoot(const wxString& text, int image, int selImage, wxTreeItemData* data)
{
    m_root = to_tree_item(m_impl->AppendContainer(wxDataViewItem(0), text, image, selImage, data));
    return m_root;
}

wxTreeItemId wxTreeCtrlDataViewBase::AppendItem(const wxTreeItemId& parent, const wxString& text, int image,
                                                [[maybe_unused]] int selImage, wxTreeItemData* data)
{
    wxDataViewItem dvitem = from_tree_item(parent);
    return to_tree_item(m_impl->AppendItem(dvitem, text, image, data));
}

wxTreeItemId wxTreeCtrlDataViewBase::AppendContainer(const wxTreeItemId& parent, const wxString& text, int image,
                                                     int selImage, wxTreeItemData* data)
{
    wxDataViewItem dvitem = from_tree_item(parent);
    return to_tree_item(m_impl->AppendContainer(dvitem, text, image, selImage, data));
}

void wxTreeCtrlDataViewBase::Collapse(const wxTreeItemId& item)
{
    wxDataViewItem dvitem = from_tree_item(item);
    m_impl->Collapse(dvitem);
}

void wxTreeCtrlDataViewBase::CollapseAll() { CollapseAllChildren(wxTreeItemId{ 0 }); }

void wxTreeCtrlDataViewBase::CollapseAllChildren(const wxTreeItemId& item)
{
    wxWindowUpdateLocker locker{ m_impl };
    // Go over all the items and collapse them recursively
    wxVector<wxDataViewItem> queue;
    queue.push_back(from_tree_item(item));
    while (!queue.empty()) {
        auto item = queue.front();
        queue.erase(queue.begin());
        m_impl->Collapse(item);

        if (m_impl->IsContainer(item)) {
            wxDataViewItemArray children;
            m_impl->GetStore()->GetChildren(item, children);
            queue.insert(queue.end(), children.begin(), children.end());
        }
    }
}

void wxTreeCtrlDataViewBase::DeleteChildren(const wxTreeItemId& item)
{
    auto dvitem = from_tree_item(item);
    m_impl->DeleteChildren(dvitem);
}

void wxTreeCtrlDataViewBase::DeleteAllItems()
{
    m_impl->DeleteAllItems();
    m_root = {};
}

void wxTreeCtrlDataViewBase::Delete(const wxTreeItemId& item)
{
    if (m_root == item) {
        m_root = {};
    }
    m_impl->DeleteItem(from_tree_item(item));
}

void wxTreeCtrlDataViewBase::EnsureVisible(const wxTreeItemId& item) { m_impl->EnsureVisible(from_tree_item(item)); }

void wxTreeCtrlDataViewBase::SortChildren([[maybe_unused]] const wxTreeItemId& item)
{
    // Not implemented for now
}

wxTreeItemId wxTreeCtrlDataViewBase::GetRootItem() const { return m_root; }

void wxTreeCtrlDataViewBase::Expand(const wxTreeItemId& item) { m_impl->Expand(from_tree_item(item)); }

wxTreeItemId wxTreeCtrlDataViewBase::GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const
{
    cookie = (wxTreeItemIdValue)0;
    return GetNextChild(item, cookie);
}

wxTreeItemId wxTreeCtrlDataViewBase::GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const
{
    size_t next_index = (size_t)cookie;
    auto parent = from_tree_item(item);
    if (m_impl->GetChildCount(parent) <= next_index) {
        return {};
    }

    auto child = to_tree_item(m_impl->GetStore()->GetNthChild(parent, next_index));
    next_index++;
    // Update the cookie
    cookie = (wxTreeItemIdValue)next_index;
    return child;
}

wxTreeItemData* wxTreeCtrlDataViewBase::GetItemData(const wxTreeItemId& item) const
{
    auto dvitem = from_tree_item(item);
    return dynamic_cast<wxTreeItemData*>(m_impl->GetItemData(dvitem));
}

wxString wxTreeCtrlDataViewBase::GetItemText(const wxTreeItemId& item) const
{
    auto dvitem = from_tree_item(item);
    return m_impl->GetItemText(dvitem);
}

wxTreeItemId wxTreeCtrlDataViewBase::GetItemParent(const wxTreeItemId& item) const
{
    auto dvitem = from_tree_item(item);
    return to_tree_item(m_impl->GetItemParent(dvitem));
}

bool wxTreeCtrlDataViewBase::ItemHasChildren(const wxTreeItemId& item) const
{
    auto dvitem = from_tree_item(item);
    return m_impl->GetStore()->GetChildCount(dvitem) > 0;
}

wxTreeItemId wxTreeCtrlDataViewBase::GetFocusedItem() const { return to_tree_item(m_impl->GetSelection()); }

void wxTreeCtrlDataViewBase::SetItemTextColour(const wxTreeItemId& item, const wxColour& col)
{
    wxUnusedVar(item);
    wxUnusedVar(col);
}

size_t wxTreeCtrlDataViewBase::GetSelections(wxArrayTreeItemIds& selections) const
{
    wxDataViewItemArray dv_selections;
    dv_selections.reserve(m_impl->GetSelectedItemsCount());

    m_impl->GetSelections(dv_selections);

    selections.reserve(dv_selections.size());
    for (const auto& dvitem : dv_selections) {
        selections.push_back(to_tree_item(dvitem));
    }
    return selections.size();
}

void wxTreeCtrlDataViewBase::SelectItem(const wxTreeItemId& item, bool select)
{
    auto dvitem = from_tree_item(item);
    if (select) {
        m_impl->UnselectAll();
        m_impl->Select(dvitem);
    } else {
        m_impl->Unselect(dvitem);
    }
}

bool wxTreeCtrlDataViewBase::IsSelected(const wxTreeItemId& item) const
{
    wxArrayTreeItemIds selections;
    GetSelections(selections);

    auto iter = std::find_if(selections.begin(), selections.end(),
                             [&item](const wxTreeItemId& selectedItem) { return selectedItem == item; });

    return iter != selections.end();
}

void wxTreeCtrlDataViewBase::SetItemText(const wxTreeItemId& item, const wxString& text)
{
    m_impl->SetItemText(from_tree_item(item), text);
}

bool wxTreeCtrlDataViewBase::IsExpanded(const wxTreeItemId& item) const
{
    return m_impl->IsExpanded(from_tree_item(item));
}

void wxTreeCtrlDataViewBase::SetItemImage(const wxTreeItemId& item, int imageId)
{
    if (!m_impl->HasImages()) {
        return;
    }
    wxBitmap bmp = m_impl->GetImageBitmapFor(this, imageId);
    if (!bmp.IsOk()) {
        return;
    }

    auto dvitem = from_tree_item(item);
    m_impl->SetItemIcon(dvitem, bmp);
}

/// ===----------------------------------------------
/// Convert DataView events -> TreeCtrl events
/// ===----------------------------------------------

void wxTreeCtrlDataViewBase::OnItemExpandingInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_EXPANDING };
    treeEvent.SetItem(to_tree_item(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);

    if (!treeEvent.IsAllowed()) {
        event.Veto();
    } else {
        event.Skip();
    }
}

void wxTreeCtrlDataViewBase::OnItemExpandedInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_EXPANDED };
    treeEvent.SetItem(to_tree_item(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}

void wxTreeCtrlDataViewBase::OnItemActivatedInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_ACTIVATED };
    treeEvent.SetItem(to_tree_item(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}

void wxTreeCtrlDataViewBase::OnItemContextMenuInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_MENU };
    treeEvent.SetItem(to_tree_item(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}
