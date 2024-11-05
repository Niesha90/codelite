//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: zoom_navigator.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "zoom_navigator.h"

// Declare the bitmap loading function
extern void wxC6745InitBitmapResources();

namespace
{
// return the wxBORDER_SIMPLE that matches the current application theme
wxBorder get_border_simple_theme_aware_bit()
{
#if wxVERSION_NUMBER >= 3300 && defined(__WXMSW__)
    return wxSystemSettings::GetAppearance().IsDark() ? wxBORDER_SIMPLE : wxBORDER_DEFAULT;
#else
    return wxBORDER_DEFAULT;
#endif
} // DoGetBorderSimpleBit
bool bBitmapLoaded = false;
} // namespace

znSettingsDlgBase::znSettingsDlgBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
                                     const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC6745InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer2);

    m_checkBoxEnableZN = new wxCheckBox(this, wxID_ANY, _("Enable ZoomNavigator"), wxDefaultPosition,
                                        wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxEnableZN->SetValue(true);

    boxSizer2->Add(m_checkBoxEnableZN, 0, wxALL | wxALIGN_LEFT, WXC_FROM_DIP(5));

    wxFlexGridSizer* flexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer12->SetFlexibleDirection(wxBOTH);
    flexGridSizer12->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer12->AddGrowableCol(1);

    boxSizer2->Add(flexGridSizer12, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText14 = new wxStaticText(this, wxID_ANY, _("Highlight colour:"), wxDefaultPosition,
                                      wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    flexGridSizer12->Add(m_staticText14, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_colourPickerHighlightColour =
        new wxColourPickerCtrl(this, wxID_ANY, wxColour(wxT("rgb(128,255,255)")), wxDefaultPosition,
                               wxDLG_UNIT(this, wxSize(-1, -1)), wxCLRP_SHOW_LABEL | wxCLRP_DEFAULT_STYLE);

    flexGridSizer12->Add(m_colourPickerHighlightColour, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText22 =
        new wxStaticText(this, wxID_ANY, _("Zoom factor:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText22->SetToolTip(
        _("Sets the preview pane zoom factor.\nValid values should be in the range of -10 and 20"));

    flexGridSizer12->Add(m_staticText22, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_spinCtrlZoomFactor = new wxSpinCtrl(this, wxID_ANY, wxT("-15"), wxDefaultPosition,
                                          wxDLG_UNIT(this, wxSize(-1, -1)), wxSP_ARROW_KEYS);
    m_spinCtrlZoomFactor->SetToolTip(
        _("Sets the preview pane zoom factor.\nValid values should be in the range of -10 and 20"));
    m_spinCtrlZoomFactor->SetRange(-15, 20);
    m_spinCtrlZoomFactor->SetValue(-15);

    flexGridSizer12->Add(m_spinCtrlZoomFactor, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText26 = new wxStaticText(this, wxID_ANY, _("Use vertical scrollbar:"), wxDefaultPosition,
                                      wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    flexGridSizer12->Add(m_staticText26, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_checkBoxUseVScrollbar =
        new wxCheckBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxUseVScrollbar->SetValue(false);

    flexGridSizer12->Add(m_checkBoxUseVScrollbar, 0, wxALL, WXC_FROM_DIP(5));

    boxSizer2->Add(0, 0, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stdBtnSizer30 = new wxStdDialogButtonSizer();

    boxSizer2->Add(m_stdBtnSizer30, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(10));

    m_button32 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_button32->SetDefault();
    m_stdBtnSizer30->AddButton(m_button32);

    m_button34 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_stdBtnSizer30->AddButton(m_button34);
    m_stdBtnSizer30->Realize();

    SetName(wxT("znSettingsDlgBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
    // Connect events
    m_button32->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &znSettingsDlgBase::OnOK, this);
}

znSettingsDlgBase::~znSettingsDlgBase()
{
    m_button32->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &znSettingsDlgBase::OnOK, this);
}
