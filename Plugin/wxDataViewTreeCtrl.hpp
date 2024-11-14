#pragma once

#include "bitmap_loader.h"

#include <wx/control.h>
#include <wx/dataview.h>
#include <wx/treebase.h>

class WXDLLIMPEXP_SDK wxTreeCtrlDataViewBaseCookie
{
public:
    wxTreeCtrlDataViewBaseCookie() {}
    bool CanNext() const { return m_index < m_children.size(); }
    wxTreeItemId Next();

private:
    wxDataViewItemArray m_children;
    size_t m_index = 0;
};

/// Drop-in replacement for wxTreeCtrl implemented using `wxDataViewTreeCtrl`
class WXDLLIMPEXP_SDK wxTreeCtrlDataViewBase : public wxControl
{
public:
    wxTreeCtrlDataViewBase();
    wxTreeCtrlDataViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxDefaultSize,
                           long style = wxTR_DEFAULT_STYLE | wxTR_MULTIPLE | wxTR_HIDE_ROOT | wxBORDER_NONE);
    virtual ~wxTreeCtrlDataViewBase();

    /// API - Implemented
    void SetBitmaps(BitmapLoader::Vec_t* bitmaps);
    wxTreeItemId AddRoot(const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL);
    wxTreeItemId AppendItem(const wxTreeItemId& parent, const wxString& text, int image = -1, int selImage = -1,
                            wxTreeItemData* data = NULL);
    wxTreeItemId AppendContainer(const wxTreeItemId& parent, const wxString& text, int image = -1, int selImage = -1,
                                 wxTreeItemData* data = NULL);
    void Collapse(const wxTreeItemId& item);
    void CollapseAll();
    void CollapseAllChildren(const wxTreeItemId& item);
    void DeleteChildren(const wxTreeItemId& item);
    void DeleteAllItems();
    void Delete(const wxTreeItemId& item);
    void EnsureVisible(const wxTreeItemId& item);
    void SortChildren(const wxTreeItemId& item);
    wxTreeItemId GetRootItem() const;
    void Expand(const wxTreeItemId& item);
    wxTreeItemId GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const;
    wxTreeItemId GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const;
    wxTreeItemData* GetItemData(const wxTreeItemId& item) const;
    wxTreeItemData* GetRootItemData() const;
    wxString GetItemText(const wxTreeItemId& item) const;
    wxTreeItemId GetItemParent(const wxTreeItemId& item) const;
    bool ItemHasChildren(const wxTreeItemId& item) const;
    wxTreeItemId GetFocusedItem() const;
    void SetItemTextColour(const wxTreeItemId& item, const wxColour& col);
    size_t GetSelections(wxArrayTreeItemIds& selections) const;
    void SelectItem(const wxTreeItemId& item, bool select = true);
    bool IsSelected(const wxTreeItemId& item) const;
    void SetItemText(const wxTreeItemId& item, const wxString& text);
    bool IsExpanded(const wxTreeItemId& item) const;
    void SetItemImage(const wxTreeItemId& item, int imageId);

protected:
    void OnItemExpandingInternal(wxDataViewEvent& event);
    void OnItemExpandedInternal(wxDataViewEvent& event);
    void OnItemActivatedInternal(wxDataViewEvent& event);
    void OnItemContextMenuInternal(wxDataViewEvent& event);

private:
    wxDataViewTreeCtrl* m_impl = nullptr;
    wxTreeItemData* m_rootItemData = nullptr;
};
