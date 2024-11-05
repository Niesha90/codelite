//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: UI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "UI.h"

// Declare the bitmap loading function
extern void wxCrafternz79PnInitBitmapResources();

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

DAPMainViewBase::DAPMainViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafternz79PnInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer237 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer237);

    m_splitterHorizontal = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                                wxSP_LIVE_UPDATE | wxSP_3DSASH);
    m_splitterHorizontal->SetSashGravity(0.5);
    m_splitterHorizontal->SetMinimumPaneSize(100);

    boxSizer237->Add(m_splitterHorizontal, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_splitterPageTop = new wxPanel(m_splitterHorizontal, wxID_ANY, wxDefaultPosition,
                                    wxDLG_UNIT(m_splitterHorizontal, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    wxBoxSizer* boxSizer289 = new wxBoxSizer(wxVERTICAL);
    m_splitterPageTop->SetSizer(boxSizer289);

    m_splitterVertical =
        new clThemedSplitterWindow(m_splitterPageTop, wxID_ANY, wxDefaultPosition,
                                   wxDLG_UNIT(m_splitterPageTop, wxSize(-1, -1)), wxSP_LIVE_UPDATE | wxSP_3DSASH);
    m_splitterVertical->SetSashGravity(0.5);
    m_splitterVertical->SetMinimumPaneSize(100);

    boxSizer289->Add(m_splitterVertical, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_splitterPageBacktrace = new wxPanel(m_splitterVertical, wxID_ANY, wxDefaultPosition,
                                          wxDLG_UNIT(m_splitterVertical, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    wxBoxSizer* boxSizer243 = new wxBoxSizer(wxHORIZONTAL);
    m_splitterPageBacktrace->SetSizer(boxSizer243);

    m_dvListCtrlThreadId =
        new clThemedListCtrl(m_splitterPageBacktrace, wxID_ANY, wxDefaultPosition,
                             wxDLG_UNIT(m_splitterPageBacktrace, wxSize(150, -1)), wxDV_ROW_LINES | wxDV_SINGLE);

    boxSizer243->Add(m_dvListCtrlThreadId, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_dvListCtrlThreadId->AppendTextColumn(_("ID"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(50), wxALIGN_LEFT,
                                           wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlThreadId->AppendTextColumn(_("Active"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(24), wxALIGN_LEFT,
                                           wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlThreadId->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                           wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlFrames =
        new clThemedListCtrl(m_splitterPageBacktrace, wxID_ANY, wxDefaultPosition,
                             wxDLG_UNIT(m_splitterPageBacktrace, wxSize(-1, -1)), wxDV_ROW_LINES | wxDV_SINGLE);

    boxSizer243->Add(m_dvListCtrlFrames, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_dvListCtrlFrames->AppendTextColumn(_("ID"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(50), wxALIGN_LEFT,
                                         wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlFrames->AppendTextColumn(_("Name"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(100), wxALIGN_LEFT,
                                         wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlFrames->AppendTextColumn(_("Line"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(100), wxALIGN_LEFT,
                                         wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrlFrames->AppendTextColumn(_("Source"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                         wxDATAVIEW_COL_RESIZABLE);
    m_splitterPageLocals = new wxPanel(m_splitterVertical, wxID_ANY, wxDefaultPosition,
                                       wxDLG_UNIT(m_splitterVertical, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_splitterVertical->SplitVertically(m_splitterPageBacktrace, m_splitterPageLocals, 0);

    wxBoxSizer* boxSizer244 = new wxBoxSizer(wxVERTICAL);
    m_splitterPageLocals->SetSizer(boxSizer244);

    m_variablesTree = new clThemedTreeCtrl(m_splitterPageLocals, wxID_ANY, wxDefaultPosition,
                                           wxDLG_UNIT(m_splitterPageLocals, wxSize(-1, -1)),
                                           wxDV_ROW_LINES | wxDV_SINGLE | wxBORDER_NONE);

    boxSizer244->Add(m_variablesTree, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_splitterPageBottom = new wxPanel(m_splitterHorizontal, wxID_ANY, wxDefaultPosition,
                                       wxDLG_UNIT(m_splitterHorizontal, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_splitterHorizontal->SplitHorizontally(m_splitterPageTop, m_splitterPageBottom, 0);

    wxBoxSizer* boxSizer290 = new wxBoxSizer(wxVERTICAL);
    m_splitterPageBottom->SetSizer(boxSizer290);

    SetName(wxT("DAPMainViewBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
    // Connect events
    m_dvListCtrlThreadId->Bind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, &DAPMainViewBase::OnThreadIdChanged, this);
    m_dvListCtrlThreadId->Bind(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, &DAPMainViewBase::OnThreadsListMenu, this);
    m_dvListCtrlFrames->Bind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, &DAPMainViewBase::OnFrameChanged, this);
}

DAPMainViewBase::~DAPMainViewBase()
{
    m_dvListCtrlThreadId->Unbind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, &DAPMainViewBase::OnThreadIdChanged, this);
    m_dvListCtrlThreadId->Unbind(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, &DAPMainViewBase::OnThreadsListMenu, this);
    m_dvListCtrlFrames->Unbind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, &DAPMainViewBase::OnFrameChanged, this);
}

DapDebuggerSettingsDlgBase::DapDebuggerSettingsDlgBase(wxWindow* parent, wxWindowID id, const wxString& title,
                                                       const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafternz79PnInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer249 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer249);

    m_toolbar = new clToolBar(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                              wxTB_HORZ_TEXT | wxTB_NODIVIDER | wxTB_FLAT);
    m_toolbar->SetToolBitmapSize(wxSize(16, 16));

    boxSizer249->Add(m_toolbar, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    boxSizer249->Add(m_panelMain, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer254 = new wxBoxSizer(wxVERTICAL);
    m_panelMain->SetSizer(boxSizer254);

    m_notebook =
        new wxNotebook(m_panelMain, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panelMain, wxSize(-1, -1)), wxBK_DEFAULT);
    m_notebook->SetName(wxT("m_notebook"));

    boxSizer254->Add(m_notebook, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stdBtnSizer250 = new wxStdDialogButtonSizer();

    boxSizer249->Add(m_stdBtnSizer250, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_button251 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_button251->SetDefault();
    m_stdBtnSizer250->AddButton(m_button251);

    m_button252 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_stdBtnSizer250->AddButton(m_button252);
    m_stdBtnSizer250->Realize();

#if wxVERSION_NUMBER >= 2900
    if (!wxPersistenceManager::Get().Find(m_notebook)) {
        wxPersistenceManager::Get().RegisterAndRestore(m_notebook);
    } else {
        wxPersistenceManager::Get().Restore(m_notebook);
    }
#endif

    SetName(wxT("DapDebuggerSettingsDlgBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
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

DapDebuggerSettingsDlgBase::~DapDebuggerSettingsDlgBase() {}

DAPBreakpointsViewBase::DAPBreakpointsViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxPanel(parent, id, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafternz79PnInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer264 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer264);

    m_toolbar =
        new clToolBar(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTB_NODIVIDER | wxTB_FLAT);
    m_toolbar->SetToolBitmapSize(wxSize(16, 16));

    boxSizer264->Add(m_toolbar, 0, 0, WXC_FROM_DIP(5));

    m_dvListCtrl = new clThemedListCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                        wxDV_ROW_LINES | wxDV_SINGLE | wxBORDER_NONE);

    boxSizer264->Add(m_dvListCtrl, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_dvListCtrl->AppendTextColumn(_("#"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT, 0);
    m_dvListCtrl->AppendTextColumn(_("?"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT, 0);
    m_dvListCtrl->AppendTextColumn(_("File"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT, 0);
    m_dvListCtrl->AppendTextColumn(_("Line"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT, 0);
    m_dvListCtrl->AppendTextColumn(_("Fullpath"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT, 0);

    SetName(wxT("DAPBreakpointsViewBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
    // Connect events
    m_dvListCtrl->Bind(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, &DAPBreakpointsViewBase::OnBreakpointsContextMenu,
                       this);
}

DAPBreakpointsViewBase::~DAPBreakpointsViewBase()
{
    m_dvListCtrl->Unbind(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, &DAPBreakpointsViewBase::OnBreakpointsContextMenu,
                         this);
}

DAPTextViewBase::DAPTextViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafternz79PnInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer267 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer267);

    m_stcTextView =
        new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxBORDER_NONE);
    // Configure the fold margin
    m_stcTextView->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stcTextView->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stcTextView->SetMarginSensitive(4, true);
    m_stcTextView->SetMarginWidth(4, 0);

    // Configure the tracker margin
    m_stcTextView->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stcTextView->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stcTextView->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stcTextView->SetMarginWidth(2, 0);
    m_stcTextView->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    m_stcTextView->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcTextView->SetMarginWidth(0, 0);

    // Configure the line symbol margin
    m_stcTextView->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcTextView->SetMarginMask(3, 0);
    m_stcTextView->SetMarginWidth(3, 0);
    // Select the lexer
    m_stcTextView->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_stcTextView->StyleClearAll();
    m_stcTextView->SetWrapMode(0);
    m_stcTextView->SetIndentationGuides(0);
    m_stcTextView->SetKeyWords(0, wxT(""));
    m_stcTextView->SetKeyWords(1, wxT(""));
    m_stcTextView->SetKeyWords(2, wxT(""));
    m_stcTextView->SetKeyWords(3, wxT(""));
    m_stcTextView->SetKeyWords(4, wxT(""));

    boxSizer267->Add(m_stcTextView, 1, wxEXPAND, WXC_FROM_DIP(5));

    SetName(wxT("DAPTextViewBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
}

DAPTextViewBase::~DAPTextViewBase() {}

DAPWatchesViewBase::DAPWatchesViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                       long style)
    : wxPanel(parent, id, pos, size, style)
{
    if (!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafternz79PnInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer275 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer275);

    m_toolbar =
        new clToolBar(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTB_NODIVIDER | wxTB_FLAT);
    m_toolbar->SetToolBitmapSize(wxSize(16, 16));

    boxSizer275->Add(m_toolbar, 0, wxEXPAND, WXC_FROM_DIP(5));

    SetName(wxT("DAPWatchesViewBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
}

DAPWatchesViewBase::~DAPWatchesViewBase() {}
