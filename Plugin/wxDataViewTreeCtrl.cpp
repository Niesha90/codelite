#include "wxDataViewTreeCtrl.hpp"
#include <wx/sizer.h>

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxControl(parent, wxID_ANY)
{
    m_impl = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(m_impl, wxSizerFlags(1).Expand());
}

wxTreeCtrlDataViewBase::wxTreeCtrlDataViewBase() {}
wxTreeCtrlDataViewBase::~wxTreeCtrlDataViewBase() {}
