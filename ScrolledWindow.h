#ifndef SCROLLEDWINDOW_H
#define SCROLLEDWINDOW_H

#include "wxPaintApp.h"
#include "BrushInterface.h"
//#include "wxPaintMain.h"

#include <wx/list.h>

class ScrolledWindow : public wxScrolledWindow
{
    DECLARE_EVENT_TABLE()
    public:
        ScrolledWindow(wxWindow* parent, wxWindowID id, wxString image_path);
        ScrolledWindow(wxWindow* parent, wxWindowID id, wxSize size);
        virtual ~ScrolledWindow();
        bool IsInitialized();
        bool IsModified();
        wxSize GetImageSize();
        void SetBrushInterface(BrushInterface *i);
        void SetCanvasSize(wxSize & sz, bool scale);
        void SaveFile(wxString & file);

    protected:
        virtual void OnDraw(wxDC& dc);
        void PutPoint( wxPoint& point );
        void _OnMouseDown( wxMouseEvent& event ) { OnMouseDown(event); }
        void _OnMouseUp( wxMouseEvent& event ) { OnMouseUp(event); }
        void _OnMouseMove( wxMouseEvent& event ) { OnMouseMove(event); }

        virtual void OnMouseDown( wxMouseEvent& event );
        virtual void OnMouseUp( wxMouseEvent& event );
        virtual void OnMouseMove( wxMouseEvent& event );
        void DrawCircle(wxPoint & point);
        void DrawStar(wxPoint & point);

        wxPen GetPen();
        wxBrush GetBrush();
        int GetBrushSize();

    private:
        wxBitmap* bitmap;
        int w,h;
        bool init_complete;
        bool is_painting;
        bool is_modified;
        wxWindow *parent;
        BrushInterface *q;
        void Initialize(wxWindow* parent, wxImage & img);
        void DoCrop();
        wxRect GetCropRect();
        int x1,y1,x2,y2;    // For crop
};

#endif // SCROLLEDWINDOW_H
