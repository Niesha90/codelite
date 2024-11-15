#include "wxDataViewTreeCtrl.hpp"

#include <algorithm>
#include <wx/sizer.h>
#include <wx/wupdlock.h>

namespace
{
wxTreeItemId ToTreeItem(const wxDataViewItem& item)
{
    wxTreeItemId tree_item(item.m_pItem);
    return tree_item;
}
wxDataViewItem FromTreeItem(const wxTreeItemId& item)
{
    wxDataViewItem dv_item(item.m_pItem);
    return dv_item;
}
} // namespace

wxTreeItemId wxTreeCtrlDataViewBaseCookie::Next()
{
    auto item = m_children[m_index];
    ++m_index;
    return ToTreeItem(item);
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
    m_rootItemData = nullptr;
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
    // Allocate fake root item
    wxUnusedVar(text);
    wxUnusedVar(image);
    wxUnusedVar(selImage);

    wxDELETE(m_rootItemData);
    m_rootItemData = data;
    return {};
}

wxTreeItemId wxTreeCtrlDataViewBase::AppendItem(const wxTreeItemId& parent, const wxString& text, int image,
                                                [[maybe_unused]] int selImage, wxTreeItemData* data)
{
    wxDataViewItem dvitem = FromTreeItem(parent);
    return ToTreeItem(m_impl->AppendItem(dvitem, text, image, data));
}

wxTreeItemId wxTreeCtrlDataViewBase::AppendContainer(const wxTreeItemId& parent, const wxString& text, int image,
                                                     int selImage, wxTreeItemData* data)
{
    wxDataViewItem dvitem = FromTreeItem(parent);
    return ToTreeItem(m_impl->AppendContainer(dvitem, text, image, selImage, data));
}

void wxTreeCtrlDataViewBase::Collapse(const wxTreeItemId& item)
{
    wxDataViewItem dvitem = FromTreeItem(item);
    m_impl->Collapse(dvitem);
}

void wxTreeCtrlDataViewBase::CollapseAll() { CollapseAllChildren(wxTreeItemId{ 0 }); }

void wxTreeCtrlDataViewBase::CollapseAllChildren(const wxTreeItemId& item)
{
    wxWindowUpdateLocker locker{ m_impl };

    // Go over all the items and collapse them recursively
    wxVector<wxDataViewItem> queue;
    queue.push_back(FromTreeItem(item));

    wxVector<wxDataViewItem> containers;
    while (!queue.empty()) {
        auto item = queue.front();
        queue.erase(queue.begin());

        if (!item.IsOk() /* <- root item */ || m_impl->IsContainer(item)) {
            containers.push_back(item);

            wxDataViewItemArray children;
            m_impl->GetStore()->GetChildren(item, children);

            // Only add container child
            for (auto child : children) {
                if (m_impl->IsContainer(child)) {
                    queue.push_back(child);
                    containers.push_back(child);
                }
            }
        }
    }

    // Collapse all children from bottom to the top
    auto iter = containers.rbegin();
    for (; iter != containers.rend(); ++iter) {
        if (m_impl->IsExpanded(*iter)) {
            m_impl->Collapse(*iter);
        }
    }
}

void wxTreeCtrlDataViewBase::DeleteChildren(const wxTreeItemId& item)
{
    auto dvitem = FromTreeItem(item);
    m_impl->DeleteChildren(dvitem);
}

void wxTreeCtrlDataViewBase::DeleteAllItems()
{
    m_impl->DeleteAllItems();
    wxDELETE(m_rootItemData);
}

void wxTreeCtrlDataViewBase::Delete(const wxTreeItemId& item)
{
    if (!item.IsOk()) {
        return;
    }
    m_impl->DeleteItem(FromTreeItem(item));
}

void wxTreeCtrlDataViewBase::EnsureVisible(const wxTreeItemId& item) { m_impl->EnsureVisible(FromTreeItem(item)); }

void wxTreeCtrlDataViewBase::SortChildren([[maybe_unused]] const wxTreeItemId& item)
{
    // Not implemented for now
}

wxTreeItemId wxTreeCtrlDataViewBase::GetRootItem() const { return wxTreeItemId{ nullptr }; }

void wxTreeCtrlDataViewBase::Expand(const wxTreeItemId& item) { m_impl->Expand(FromTreeItem(item)); }

wxTreeItemId wxTreeCtrlDataViewBase::GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const
{
    cookie = (wxTreeItemIdValue)0;
    return GetNextChild(item, cookie);
}

wxTreeItemId wxTreeCtrlDataViewBase::GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const
{
    size_t next_index = (size_t)cookie;
    auto parent = FromTreeItem(item);
    if (m_impl->GetChildCount(parent) <= next_index) {
        return {};
    }

    auto child = ToTreeItem(m_impl->GetStore()->GetNthChild(parent, next_index));
    next_index++;
    // Update the cookie
    cookie = (wxTreeItemIdValue)next_index;
    return child;
}

wxTreeItemData* wxTreeCtrlDataViewBase::GetItemData(const wxTreeItemId& item) const
{
    if (!item.IsOk()) {
        // the root
        return m_rootItemData;
    }

    auto dvitem = FromTreeItem(item);
    return dynamic_cast<wxTreeItemData*>(m_impl->GetItemData(dvitem));
}

wxTreeItemData* wxTreeCtrlDataViewBase::GetRootItemData() const
{
    // the root
    return m_rootItemData;
}

wxString wxTreeCtrlDataViewBase::GetItemText(const wxTreeItemId& item) const
{
    auto dvitem = FromTreeItem(item);
    return m_impl->GetItemText(dvitem);
}

wxTreeItemId wxTreeCtrlDataViewBase::GetItemParent(const wxTreeItemId& item) const
{
    auto dvitem = FromTreeItem(item);
    return ToTreeItem(m_impl->GetItemParent(dvitem));
}

bool wxTreeCtrlDataViewBase::ItemHasChildren(const wxTreeItemId& item) const
{
    auto dvitem = FromTreeItem(item);
    return m_impl->GetStore()->GetChildCount(dvitem) > 0;
}

wxTreeItemId wxTreeCtrlDataViewBase::GetFocusedItem() const { return ToTreeItem(m_impl->GetSelection()); }

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
        selections.push_back(ToTreeItem(dvitem));
    }
    return selections.size();
}

void wxTreeCtrlDataViewBase::SelectItem(const wxTreeItemId& item, bool select)
{
    auto dvitem = FromTreeItem(item);
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
    m_impl->SetItemText(FromTreeItem(item), text);
}

bool wxTreeCtrlDataViewBase::IsExpanded(const wxTreeItemId& item) const
{
    return m_impl->IsExpanded(FromTreeItem(item));
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

    auto dvitem = FromTreeItem(item);
    m_impl->SetItemIcon(dvitem, bmp);
}

/// ===----------------------------------------------
/// Convert DataView events -> TreeCtrl events
/// ===----------------------------------------------

void wxTreeCtrlDataViewBase::OnItemExpandingInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_EXPANDING };
    treeEvent.SetItem(ToTreeItem(event.GetItem()));
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
    treeEvent.SetItem(ToTreeItem(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}

void wxTreeCtrlDataViewBase::OnItemActivatedInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_ACTIVATED };
    treeEvent.SetItem(ToTreeItem(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}

void wxTreeCtrlDataViewBase::OnItemContextMenuInternal(wxDataViewEvent& event)
{
    wxTreeEvent treeEvent{ wxEVT_TREE_ITEM_MENU };
    treeEvent.SetItem(ToTreeItem(event.GetItem()));
    treeEvent.SetEventObject(this);
    GetEventHandler()->ProcessEvent(treeEvent);
    event.Skip();
}
