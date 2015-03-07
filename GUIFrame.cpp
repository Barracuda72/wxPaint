///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 14 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 620,260 ), wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* newFile;
	newFile = new wxMenuItem( fileMenu, wxID_NEW, wxString( wxT("&New") ) + wxT('\t') + wxT("CTRL+N"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( newFile );
	
	wxMenuItem* openFile;
	openFile = new wxMenuItem( fileMenu, wxID_OPEN, wxString( wxT("&Open") ) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( openFile );
	
	wxMenuItem* m_separator1;
	m_separator1 = fileMenu->AppendSeparator();
	
	wxMenuItem* saveFile;
	saveFile = new wxMenuItem( fileMenu, wxID_SAVE, wxString( wxT("&Save") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( saveFile );
	
	wxMenuItem* saveAs;
	saveAs = new wxMenuItem( fileMenu, wxID_SAVEAS, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( saveAs );
	
	wxMenuItem* m_separator2;
	m_separator2 = fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, wxID_EXIT, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") ); 
	
	imageMenu = new wxMenu();
	wxMenuItem* canvasSizeImage;
	canvasSizeImage = new wxMenuItem( imageMenu, ctID_CANVASSIZE, wxString( wxT("Can&vas size...") ) , wxEmptyString, wxITEM_NORMAL );
	imageMenu->Append( canvasSizeImage );
	
	mbar->Append( imageMenu, wxT("&Image") ); 
	
	windowMenu = new wxMenu();
	wxMenuItem* cascadeWindow;
	cascadeWindow = new wxMenuItem( windowMenu, ctID_CASCADE, wxString( wxT("&Cascade") ) , wxEmptyString, wxITEM_NORMAL );
	windowMenu->Append( cascadeWindow );
	
	wxMenuItem* leftToRightWindow;
	leftToRightWindow = new wxMenuItem( windowMenu, ctID_LEFTTORIGHT, wxString( wxT("&Left To Right") ) , wxEmptyString, wxITEM_NORMAL );
	windowMenu->Append( leftToRightWindow );
	
	wxMenuItem* topToBottomWindow;
	topToBottomWindow = new wxMenuItem( windowMenu, ctID_TOPTOBOTTOM, wxString( wxT("&Top to bottom") ) , wxEmptyString, wxITEM_NORMAL );
	windowMenu->Append( topToBottomWindow );
	
	wxMenuItem* arrangeIconsWindow;
	arrangeIconsWindow = new wxMenuItem( windowMenu, ctID_ARRANGEICONS, wxString( wxT("A&rrange icons") ) , wxEmptyString, wxITEM_NORMAL );
	windowMenu->Append( arrangeIconsWindow );
	
	wxMenuItem* minimizeAll;
	minimizeAll = new wxMenuItem( windowMenu, ctID_MINIMIZEALL, wxString( wxT("&Minimize all") ) , wxEmptyString, wxITEM_NORMAL );
	windowMenu->Append( minimizeAll );
	
	mbar->Append( windowMenu, wxT("&Window") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, wxID_ABOUT, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_main_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer2->Add( m_main_panel, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_choice_brush = new wxComboBox( m_toolBar, wxID_ANY, wxT("Red"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY );
	m_choice_brush->Append( wxT("Red") );
	m_choice_brush->Append( wxT("Green") );
	m_choice_brush->Append( wxT("Blue") );
	m_choice_brush->Append( wxT("Other...") );
	m_toolBar->AddControl( m_choice_brush );
	m_toolBar->AddSeparator(); 
	m_staticText3 = new wxStaticText( m_toolBar, wxID_ANY, wxT("Brush:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_toolBar->AddControl( m_staticText3 );
	wxString m_choice_starChoices[] = { wxT("Circle"), wxT("Star"), wxT("Crop") };
	int m_choice_starNChoices = sizeof( m_choice_starChoices ) / sizeof( wxString );
	m_choice_star = new wxChoice( m_toolBar, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_starNChoices, m_choice_starChoices, 0 );
	m_choice_star->SetSelection( 0 );
	m_toolBar->AddControl( m_choice_star );
	m_spinCtrl_brush = new wxSpinCtrl( m_toolBar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );
	m_toolBar->AddControl( m_spinCtrl_brush );
	m_staticText_star = new wxStaticText( m_toolBar, wxID_ANY, wxT("Corners"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_star->Wrap( -1 );
	m_toolBar->AddControl( m_staticText_star );
	m_spinCtrl_corners = new wxSpinCtrl( m_toolBar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 3, 30, 0 );
	m_toolBar->AddControl( m_spinCtrl_corners );
	m_checkBox_star = new wxCheckBox( m_toolBar, wxID_ANY, wxT("Filled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar->AddControl( m_checkBox_star );
	m_toolBar->Realize();
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( newFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnNewFile ) );
	this->Connect( openFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpenFile ) );
	this->Connect( saveFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveFile ) );
	this->Connect( saveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveFileAs ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( canvasSizeImage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCanvasSizeSelected ) );
	this->Connect( cascadeWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCascadeWindow ) );
	this->Connect( leftToRightWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLeftToRight ) );
	this->Connect( topToBottomWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnTopToBottom ) );
	this->Connect( arrangeIconsWindow->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnTileWindow ) );
	this->Connect( minimizeAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMinimizeAll ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	m_main_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUIFrame::OnMainPanelUpdate ), NULL, this );
	m_choice_star->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnStarChoiceChanged ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnNewFile ) );
	this->Disconnect( wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpenFile ) );
	this->Disconnect( wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveFile ) );
	this->Disconnect( wxID_SAVEAS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnSaveFileAs ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( ctID_CANVASSIZE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCanvasSizeSelected ) );
	this->Disconnect( ctID_CASCADE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCascadeWindow ) );
	this->Disconnect( ctID_LEFTTORIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLeftToRight ) );
	this->Disconnect( ctID_TOPTOBOTTOM, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnTopToBottom ) );
	this->Disconnect( ctID_ARRANGEICONS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnTileWindow ) );
	this->Disconnect( ctID_MINIMIZEALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMinimizeAll ) );
	this->Disconnect( wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	m_main_panel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUIFrame::OnMainPanelUpdate ), NULL, this );
	m_choice_star->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnStarChoiceChanged ), NULL, this );
	
}

ResizeGUI::ResizeGUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 320,135 ), wxSize( 320,135 ) );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer4->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrl_width = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2000, 0 );
	bSizer4->Add( m_spinCtrl_width, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer4->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinCtrl_height = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2000, 0 );
	bSizer4->Add( m_spinCtrl_height, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_checkBox_scale = new wxCheckBox( this, wxID_ANY, wxT("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_checkBox_scale, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button_ok = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button_ok, 0, wxALL, 5 );
	
	m_button_cancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_button_cancel, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button_ok->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUI::OnOkButtonClick ), NULL, this );
	m_button_cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUI::OnCancelButtonClick ), NULL, this );
}

ResizeGUI::~ResizeGUI()
{
	// Disconnect Events
	m_button_ok->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUI::OnOkButtonClick ), NULL, this );
	m_button_cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ResizeGUI::OnCancelButtonClick ), NULL, this );
	
}
