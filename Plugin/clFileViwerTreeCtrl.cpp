#include "clFileViwerTreeCtrl.h"

wxIMPLEMENT_DYNAMIC_CLASS(clFileViewerTreeCtrl, wxTreeCtrl);

// Default Ctor - required by wxIMPLEMENT_DYNAMIC_CLASS macro
clFileViewerTreeCtrl::clFileViewerTreeCtrl()
    : wxTreeCtrl()
{
}

clFileViewerTreeCtrl::clFileViewerTreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                           long style)
    : wxTreeCtrl(parent, id, pos, size, (style | wxTR_FULL_ROW_HIGHLIGHT))
{
#if 0
    std::function<bool(const wxTreeItemId&, const wxTreeItemId&)> SortFunc = [&](const wxTreeItemId& itemA,
                                                                                 const wxTreeItemId& itemB) {
        clTreeCtrlData* a = static_cast<clTreeCtrlData*>(GetItemData(itemA));
        clTreeCtrlData* b = static_cast<clTreeCtrlData*>(GetItemData(itemB));
        if(a->IsFolder() && b->IsFile())
            return true;
        else if(b->IsFolder() && a->IsFile())
            return false;
        // same kind
        return (a->GetName().CmpNoCase(b->GetName()) < 0);
    };
    SetSortFunction(SortFunc);
#endif
}

clFileViewerTreeCtrl::~clFileViewerTreeCtrl() {}

int clFileViewerTreeCtrl::OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
{
    auto item1_data = GetItemData(item1);
    auto item2_data = GetItemData(item2);
    if (item1_data == nullptr || item2_data == nullptr) {
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }

    auto d1 = dynamic_cast<clTreeCtrlData*>(item1_data);
    auto d2 = dynamic_cast<clTreeCtrlData*>(item2_data);

    if (d1 == nullptr || d2 == nullptr) {
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }

    if (d1->IsFolder() && d2->IsFile()) {
        return -1;
    } else if (d2->IsFolder() && d1->IsFile()) {
        return 1;
    } else {
        // of the same type
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }
}

void clFileViewerTreeCtrl::SetBitmaps(BitmapLoader::Vec_t* bitmaps)
{
    // Covnert to wxVector<wxBitmapBundle>
    wxVector<wxBitmapBundle> images;
    images.reserve(bitmaps->size());

    m_bitmaps = bitmaps;
    images.insert(images.begin(), m_bitmaps->begin(), m_bitmaps->end());
    SetImages(images);
}

wxTreeItemId clTreeNodeIndex::Find(const wxString& path)
{
#ifdef __WXMSW__
    wxString lcpath = path.Lower();
    if (m_children.count(lcpath)) {
        return m_children.find(lcpath)->second;
    }
#else
    if (m_children.count(path)) {
        return m_children.find(path)->second;
    }
#endif
    return wxTreeItemId();
}

void clTreeNodeIndex::Add(const wxString& path, const wxTreeItemId& item)
{
    m_children.insert({
#ifdef __WXMSW__
        path.Lower()
#else
        path
#endif
            ,
        item });
}

void clTreeNodeIndex::Delete(const wxString& name)
{
    m_children.erase(
#ifdef __WXMSW__
        name.Lower()
#else
        name
#endif
    );
}
