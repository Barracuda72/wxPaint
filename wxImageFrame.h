/***************************************************************
 * Name:      wxImageFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Barracuda72 (barracuda72@bk.ru)
 * Created:   2015-03-01
 * Copyright: Barracuda72 (http://lleo.aha.ru/na)
 * License:
 **************************************************************/

#ifndef WXIMAGEFRAME_H
#define WXIMAGEFRAME_H

#include "wxPaintApp.h"
//#include "wxPaintMain.h"
#include "ScrolledWindow.h"
#include "BrushInterface.h"

//#include <wx/minifram.h>
#include <wx/artprov.h>
#include <wx/cursor.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <wx/filename.h>

class wxImageFrame : public wxPanel
{
    DECLARE_EVENT_TABLE()
    public:
        static int img_count;
    private:
        BrushInterface *q;
        ScrolledWindow *image;
        bool dragging, resizing, registered;
        int x,y;
        int w,h;
        wxWindow* parent;
        wxString title;
        wxString filename;
        wxBitmap closeBitmap;
        wxBitmap minimizeBitmap;
        wxSizerItem *footer;
        bool is_minimized;

        static const int resize_height = 15;
        static const int border_size = 4;
        static const int header_height = 15;
        static const int footer_height = 15;

        void _OnClose( wxCloseEvent& event ){ OnClose( event ); }
        void _OnMove( wxMoveEvent& event ){ OnMove( event ); }
        void _OnMouseDown( wxMouseEvent& event ) { OnMouseDown(event); }
        void _OnMouseUp( wxMouseEvent& event ) { OnMouseUp(event); }
        void _OnMouseMove( wxMouseEvent& event ) { OnMouseMove(event); }
        void _OnMouseLeave( wxMouseEvent& event ) { OnMouseLeave(event); }
        void _OnPaint( wxPaintEvent& event ) { OnPaint(event); }
        void _OnSetFocus( wxFocusEvent& event ) { OnSetFocus(event); }
        void _OnKillFocus( wxFocusEvent& event ) { OnKillFocus(event); }
        static int GetImgCount(){ return ++img_count; }

    protected:
        wxRect GetHeaderRect();
        wxRect GetFooterRect();
        wxRect GetCloseRect();
        wxRect GetMinimizeRect();
        wxRect GetResizeRect();
        void Initialize(wxWindow *parent, BrushInterface *i, const wxString & name);

        virtual void OnClose( wxCloseEvent& event );
        virtual void OnMove( wxMoveEvent& event ) { event.Skip(); };
        virtual void OnMouseDown( wxMouseEvent& event );
        virtual void OnMouseUp( wxMouseEvent& event );
        virtual void OnMouseMove( wxMouseEvent& event );
        virtual void OnPaint( wxPaintEvent& event );
        virtual void OnMouseLeave( wxMouseEvent& event );
        virtual void OnSetFocus( wxFocusEvent& event );
        virtual void OnKillFocus( wxFocusEvent& event );

    public:
        wxImageFrame(wxWindow *parent, wxWindowID id=wxID_ANY, const wxString &title=wxEmptyString,
            const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize,
            BrushInterface *b=NULL,
            long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);

        wxImageFrame(wxWindow *parent, wxWindowID id=wxID_ANY, const wxSize &imgsize=wxSize(100,100),
            const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize,
            BrushInterface *b=NULL,
            long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);

        virtual ~wxImageFrame();
        void SetBrushInterface(BrushInterface *i);
        bool isActive;
        void DoRefresh();
        void SetCanvasSize(wxSize & sz, bool scale);
        wxSize GetImageSize();
        void SaveImageFile();
        void SaveImageFileAs();
        static const int full_header_height = border_size + header_height;
        void Minimize();
        void Restore();
};

#endif // WXIMAGEFRAME_H
