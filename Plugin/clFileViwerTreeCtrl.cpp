#include "clFileViwerTreeCtrl.h"

wxIMPLEMENT_DYNAMIC_CLASS(clFileViewerTreeCtrl, wxTreeCtrl);

size_t clTreeCtrlData::GetSortScore() const
{
    size_t score = 0;
    if (IsFolder() || IsDummy()) {
        score += 100;
    }

    if (!GetName().empty()) {
        auto ch = GetName()[0];
        if (ch == '_' || ch == '.') {
            // Hidden file
            score += 10;
        }
    }
    return score;
}

// Default Ctor - required by wxIMPLEMENT_DYNAMIC_CLASS macro
clFileViewerTreeCtrl::clFileViewerTreeCtrl()
    : wxTreeCtrlDataViewBase()
{
}

clFileViewerTreeCtrl::clFileViewerTreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                           long style)
    : wxTreeCtrlDataViewBase(parent, id, pos, size, (style | wxTR_FULL_ROW_HIGHLIGHT))
{
}

clFileViewerTreeCtrl::~clFileViewerTreeCtrl() {}

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
