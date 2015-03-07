///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 14 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ctID_CANVASSIZE 1000
#define ctID_CASCADE 1001
#define ctID_LEFTTORIGHT 1002
#define ctID_TOPTOBOTTOM 1003
#define ctID_ARRANGEICONS 1004
#define ctID_MINIMIZEALL 1005

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* imageMenu;
		wxMenu* windowMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxPanel* m_main_panel;
		wxToolBar* m_toolBar;
		wxComboBox* m_choice_brush;
		wxStaticText* m_staticText3;
		wxChoice* m_choice_star;
		wxSpinCtrl* m_spinCtrl_brush;
		wxStaticText* m_staticText_star;
		wxSpinCtrl* m_spinCtrl_corners;
		wxCheckBox* m_checkBox_star;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnNewFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveFileAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCanvasSizeSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCascadeWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftToRight( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTopToBottom( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTileWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMinimizeAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMainPanelUpdate( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnStarChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxWidgets Application Template"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,260 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ResizeGUI
///////////////////////////////////////////////////////////////////////////////
class ResizeGUI : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxSpinCtrl* m_spinCtrl_width;
		wxStaticText* m_staticText2;
		wxSpinCtrl* m_spinCtrl_height;
		wxStaticLine* m_staticline1;
		wxCheckBox* m_checkBox_scale;
		
		wxButton* m_button_ok;
		wxButton* m_button_cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOkButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ResizeGUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Canvas size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 320,135 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ResizeGUI();
	
};

#endif //__GUIFrame__
