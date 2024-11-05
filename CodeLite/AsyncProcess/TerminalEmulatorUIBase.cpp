//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: TerminalEmulatorUI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "TerminalEmulatorUIBase.h"

#include "codelite_exports.h"

// Declare the bitmap loading function
extern void wxCB1DAInitBitmapResources();

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

TerminalEmulatorUIBase::TerminalEmulatorUIBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxPanel(parent, id, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCB1DAInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer2);

    m_stc = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxBORDER_NONE);
    // Configure the fold margin
    m_stc->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stc->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stc->SetMarginSensitive(4, true);
    m_stc->SetMarginWidth(4, 0);

    // Configure the tracker margin
    m_stc->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stc->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stc->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stc->SetMarginWidth(2, 0);
    m_stc->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    m_stc->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stc->SetMarginWidth(0, 0);

    // Configure the line symbol margin
    m_stc->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stc->SetMarginMask(3, 0);
    m_stc->SetMarginWidth(3, 0);
    // Select the lexer
    m_stc->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_stc->StyleClearAll();
    m_stc->SetWrapMode(0);
    m_stc->SetIndentationGuides(0);
    m_stc->SetKeyWords(0, wxT(""));
    m_stc->SetKeyWords(1, wxT(""));
    m_stc->SetKeyWords(2, wxT(""));
    m_stc->SetKeyWords(3, wxT(""));
    m_stc->SetKeyWords(4, wxT(""));

    boxSizer2->Add(m_stc, 1, wxALL | wxEXPAND, WXC_FROM_DIP(2));

    m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                wxTE_PROCESS_ENTER);
    m_textCtrl->SetFocus();
#if wxVERSION_NUMBER >= 3000
    m_textCtrl->SetHint(_("Send command to the process"));
#endif

    boxSizer2->Add(m_textCtrl, 0, wxALL | wxEXPAND, WXC_FROM_DIP(2));

    SetName(wxT("TerminalEmulatorUIBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
    // Connect events
    m_textCtrl->Bind(wxEVT_COMMAND_TEXT_ENTER, &TerminalEmulatorUIBase::OnSendCommand, this);
}

TerminalEmulatorUIBase::~TerminalEmulatorUIBase()
{
    m_textCtrl->Unbind(wxEVT_COMMAND_TEXT_ENTER, &TerminalEmulatorUIBase::OnSendCommand, this);
}

TerminalEmulatorFrameBase::TerminalEmulatorFrameBase(wxWindow* parent, wxWindowID id, const wxString& title,
                                                     const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCB1DAInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer10 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer10);

    SetName(wxT("TerminalEmulatorFrameBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
    if (GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    if (!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
}

TerminalEmulatorFrameBase::~TerminalEmulatorFrameBase() {}
