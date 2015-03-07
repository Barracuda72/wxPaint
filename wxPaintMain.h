/***************************************************************
 * Name:      wxPaintMain.h
 * Purpose:   Defines Application Frame
 * Author:    Barracuda72 (barracuda72@bk.ru)
 * Created:   2015-03-01
 * Copyright: Barracuda72 (http://lleo.aha.ru/na)
 * License:
 **************************************************************/

#ifndef WXPAINTMAIN_H
#define WXPAINTMAIN_H



#include "wxPaintApp.h"
#include "wxImageFrame.h"
#include "BrushInterface.h"

#include "GUIFrame.h"

// Workaround
#define WXBLUE_PEN_MISSING 1

class wxPaintFrame: public GUIFrame, BrushInterface
{
    public:
        wxPaintFrame(wxFrame *frame);
        ~wxPaintFrame();

        virtual wxPen GetPen() { return GetPen(m_combo_brush->GetSelection()); }
        virtual wxBrush GetBrush() { return GetBrush(m_combo_brush->GetSelection()); }
        virtual int GetBrushSize();
        virtual void SetActiveChild(wxWindow *w);
        virtual wxWindow *GetActiveChild();
        virtual void RegisterMDIWindow(wxWindow *w);
        virtual void UnregisterMDIWindow(wxWindow *w);
        virtual int GetStarCorners();
        virtual bool IsStarFilled();
        virtual bool IsCropActive();

    private:
        wxBitmapComboBox *m_combo_brush;
        wxMenuItem *save, *saveAs, *canvasSize;

        virtual void OnMainPanelUpdate( wxUpdateUIEvent& event );
        virtual void OnStarChoiceChanged( wxCommandEvent& event );

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnCanvasSizeSelected( wxCommandEvent& event );
        virtual void OnComboSelected(wxCommandEvent& event);
        virtual void OnMinimizeAll( wxCommandEvent& event );

        virtual void OnNewFile( wxCommandEvent& event );
		virtual void OnOpenFile( wxCommandEvent& event );
		virtual void OnSaveFile( wxCommandEvent& event );
		virtual void OnSaveFileAs( wxCommandEvent& event );

		virtual void OnCascadeWindow( wxCommandEvent& event );
		virtual void OnLeftToRight( wxCommandEvent& event );
		virtual void OnTopToBottom( wxCommandEvent& event );
		virtual void OnTileWindow( wxCommandEvent& event );

        void Dummy(wxString msg);
        void PostCreate(wxImageFrame *f);
        void NewImage();
        void DrawPreviewCircle(wxMemoryDC & tdc, int n);
        void ToggleStarPanel();
        wxImageFrame *GetTopImageFrame();

        void ComboInit();
        void LoadImage(wxString & name);
        wxPen GetPen(int n);
        wxBrush GetBrush(int n);
        wxColor GetColor(int n);
        wxColor otherColor;
        wxWindowList *images;
        wxImageFrame *activeChild;
        void DoClose();

// Workaround
#ifdef WXBLUE_PEN_MISSING
        wxPen *wxBLUE_PEN;
#endif
};

#endif // WXPAINTMAIN_H
