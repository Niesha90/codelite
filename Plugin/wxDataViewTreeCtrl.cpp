#include "wxDataViewTreeCtrl.hpp"

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

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxControl(parent, wxID_ANY)
{
    m_impl = new wxDataViewTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(m_impl, wxSizerFlags(1).Expand());
}

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase() {}
wxTreeCtrlDataViewBase::~wxTreeCtrlDataViewBase() {}

void wxTreeCtrlDataViewBase::SetBitmaps(BitmapLoader::Vec_t* bitmaps)
{
    wxDataViewTreeCtrl::Images images;
    images.reserve(bitmaps->size());
    images.insert(images.end(), bitmaps->begin(), bitmaps->end());

    m_impl->SetImages(images);
}

wxTreeItemId wxTreeCtrlDataViewBase::AddRoot(const wxString& text, int image, int selImage, wxTreeItemData* data)
{
    auto item = m_impl->AppendItem(wxDataViewItem(0), text, image, data);
    return to_tree_item(item);
}

wxTreeItemId wxTreeCtrlDataViewBase::AppendItem(const wxTreeItemId& parent, const wxString& text, int image,
                                                [[maybe_unused]] int selImage, wxTreeItemData* data)
{
    wxDataViewItem dvitem = from_tree_item(parent);
    return to_tree_item(m_impl->AppendItem(dvitem, text, image, data));
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

void wxTreeCtrlDataViewBase::DeleteAllItems() { m_impl->DeleteAllItems(); }

void wxTreeCtrlDataViewBase::Delete(const wxTreeItemId& item) { m_impl->DeleteItem(from_tree_item(item)); }

void wxTreeCtrlDataViewBase::EnsureVisible(const wxTreeItemId& item) { m_impl->EnsureVisible(from_tree_item(item)); }

void wxTreeCtrlDataViewBase::SortChildren([[maybe_unused]] const wxTreeItemId& item)
{
    // Not implemented for now
}

wxTreeItemId wxTreeCtrlDataViewBase::GetRootItem() const { return wxTreeItemId{ 0 }; }

void wxTreeCtrlDataViewBase::Expand(const wxTreeItemId& item) { m_impl->Expand(from_tree_item(item)); }

wxTreeItemId wxTreeCtrlDataViewBase::GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const
{

}