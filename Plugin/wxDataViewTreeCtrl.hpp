#pragma once

#include "bitmap_loader.h"

#include <wx/control.h>
#include <wx/dataview.h>
#include <wx/treebase.h>

/// Drop-in replacement for wxTreeCtrl implemented using
class wxTreeCtrlDataViewBase : public wxControl
{
public:
    wxTreeCtrlDataViewBase();
    wxTreeCtrlDataViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxDefaultSize,
                           long style = wxTR_DEFAULT_STYLE | wxTR_MULTIPLE | wxTR_HIDE_ROOT | wxBORDER_NONE);
    virtual ~wxTreeCtrlDataViewBase();

    /// API
    wxTreeItemId AddRoot(const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL);
    wxTreeItemId AppendItem(const wxTreeItemId& parent, const wxString& text, int image = -1, int selImage = -1,
                            wxTreeItemData* data = NULL);
    void Collapse(const wxTreeItemId& item);
    void CollapseAll();
    void CollapseAllChildren(const wxTreeItemId& item);
    void Delete(const wxTreeItemId& item);
    void DeleteAllItems();
    void DeleteChildren(const wxTreeItemId& item);
    void EnsureVisible(const wxTreeItemId& item);
    void Expand(const wxTreeItemId& item);
    void ExpandAll();
    void ExpandAllChildren(const wxTreeItemId& item);
    wxTreeItemId GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const;
    wxTreeItemId GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const;
    wxTreeItemId GetFirstVisibleItem() const;
    wxTreeItemData* GetItemData(const wxTreeItemId& item) const;
    wxString GetItemText(const wxTreeItemId& item) const;
    wxTreeItemId GetItemParent(const wxTreeItemId& item) const;
    void SortChildren(const wxTreeItemId& item);
    wxTreeItemId GetRootItem() const;
    void SetBitmaps(BitmapLoader::Vec_t* bitmaps);
    bool ItemHasChildren(const wxTreeItemId& item) const;
    wxTreeItemId GetFocusedItem() const;
    void SetItemTextColour(const wxTreeItemId& item, const wxColour& col);
    size_t GetSelections(wxArrayTreeItemIds& selection) const;
    void SelectItem(const wxTreeItemId& item, bool select = true);
    bool IsSelected(const wxTreeItemId& item) const;
    void SetItemText(const wxTreeItemId& item, const wxString& text);
    bool IsExpanded(const wxTreeItemId& item) const;

private:
    wxDataViewListCtrl* m_impl = nullptr;
};
