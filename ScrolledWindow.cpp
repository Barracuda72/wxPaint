#include "ScrolledWindow.h"

BEGIN_EVENT_TABLE(ScrolledWindow, wxScrolledWindow)
    EVT_LEFT_DOWN( ScrolledWindow::_OnMouseDown )
    EVT_LEFT_UP( ScrolledWindow::_OnMouseUp )
    EVT_MOTION( ScrolledWindow::_OnMouseMove )
END_EVENT_TABLE()

ScrolledWindow::ScrolledWindow(wxWindow* parent, wxWindowID id, wxString image_path)
    : wxScrolledWindow(parent, id)
{
    //ctor

    wxImage image(image_path);

    Initialize(parent, image);
}

ScrolledWindow::ScrolledWindow(wxWindow* parent, wxWindowID id, wxSize size)
    : wxScrolledWindow(parent, id)
{
    wxImage image(size.GetWidth(), size.GetHeight());

    // Clear image
    image.Replace(0,0,0,0xFF,0xFF,0xFF);

    Initialize(parent, image);
}

ScrolledWindow::~ScrolledWindow()
{
    //dtor
    delete bitmap;
}

void ScrolledWindow::Initialize(wxWindow* parent, wxImage & img)
{
    init_complete = false;
    is_painting = false;
    is_modified = false;

    if(!img.IsOk())
    {
        //wxMessageBox(wxT("there was an error loading the image"));
        return;
    }

    w = img.GetWidth();
    h = img.GetHeight();

    /* init scrolled area size, scrolling speed, etc. */
    SetScrollbars(1,1, w, h, 0, 0);

    bitmap = new wxBitmap( img );

    this->parent = parent;

    init_complete = true;
}

void ScrolledWindow::OnDraw(wxDC& dc)
{
    if (init_complete)
    {
        dc.DrawBitmap(*bitmap, 0, 0, false);
        if (q->IsCropActive() && is_painting)
        {
            dc.SetPen(*wxBLACK_PEN);
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            dc.DrawRectangle(GetCropRect());
        }
    }
}

bool ScrolledWindow::IsInitialized()
{
    return init_complete;
}

bool ScrolledWindow::IsModified()
{
    return is_modified;
}

wxSize ScrolledWindow::GetImageSize()
{
    return wxSize(w, h);
}

void ScrolledWindow::OnMouseDown( wxMouseEvent& event )
{
    //std::cout << "Down" << std::endl;
    is_modified = true;
    is_painting = true;
    CaptureMouse();

    x1 = -1;
    y1 = -1;

    wxPoint point = CalcUnscrolledPosition(event.GetPosition());
    PutPoint(point);
    // Put parent window up
    parent->Raise();
    q->SetActiveChild(parent);

}

void ScrolledWindow::OnMouseUp( wxMouseEvent& event )
{
    //std::cout << "Up" << std::endl;
    ReleaseMouse();
    is_painting = false;
    if (q->IsCropActive())
    {
        DoCrop();
        this->Refresh();
    }
}

void ScrolledWindow::OnMouseMove( wxMouseEvent& event )
{
    //std::cout << "Move" << std::endl;
    if (is_painting)
    {
        wxPoint point = CalcUnscrolledPosition(event.GetPosition());
        PutPoint(point);
    }
}

void ScrolledWindow::DrawCircle(wxPoint & point)
{
    wxMemoryDC tdc;
    tdc.SelectObject(*bitmap);

    wxPen p = GetPen();
    tdc.SetPen(p);
    tdc.SetBrush(GetBrush());

    tdc.DrawLine(x1,y1,x2,y2);
    x1 = x2;
    y1 = y2;
    /*p.SetWidth(1);
    tdc.SetPen(p);
    tdc.DrawCircle(point.x, point.y, GetBrushSize());*/

    tdc.SelectObject(wxNullBitmap);
}

void ScrolledWindow::DrawStar(wxPoint & point)
{
    wxMemoryDC tdc;
    tdc.SelectObject(*bitmap);

    wxPen pen = GetPen();
    pen.SetWidth(1);
    tdc.SetPen(pen);
    if(q->IsStarFilled())
        tdc.SetBrush(GetBrush());
    else
        tdc.SetBrush(*wxTRANSPARENT_BRUSH);

    // Generate coord list
    wxList p;

    int n = q->GetStarCorners();
    int r = q->GetBrushSize();

    int i,x,y;
    float step = 2*M_PI/n;
    float c = 0.3f;
    wxPoint *t;

    for (i = 0; i < n; i++)
    {
        // For eash star ray we need 3 points: ray peak and two by it sides
        // Peak
        x = r*cos(i*step);
        y = r*sin(i*step);

        t = new wxPoint(x, y);
        p.Append((wxObject *)t);
        // Side point
        x = r*c*cos(i*step + step/2);
        y = r*c*sin(i*step + step/2);

        t = new wxPoint(x, y);
        p.Append((wxObject *)t);
    }

    tdc.DrawPolygon(&p, point.x, point.y);

    wxList::iterator s;
    for(s = p.begin(); s != p.end(); ++s)
    {
        t = (wxPoint *)*s;
        delete t;
    }
    //tdc.DrawCircle(point.x, point.y, GetBrushSize());

    tdc.SelectObject(wxNullBitmap);
}

void ScrolledWindow::PutPoint( wxPoint& point )
{
    if (x1 == -1 && y1 == -1)
    {
        x1 = point.x;
        y1 = point.y;
    }

        x2 = point.x;
        y2 = point.y;
    if (q->GetStarCorners() != 0)
        DrawStar(point);
    else
        DrawCircle(point);

    this->Refresh();
}

wxPen ScrolledWindow::GetPen()
{
    //return *wxWHITE_PEN;
    return q->GetPen();
}

wxBrush ScrolledWindow::GetBrush()
{
    //return *wxWHITE_BRUSH;
    return q->GetBrush();
}

int ScrolledWindow::GetBrushSize()
{
    return q->GetBrushSize();
}

void ScrolledWindow::SetBrushInterface(BrushInterface *i)
{
    q = i;
}

void ScrolledWindow::SetCanvasSize(wxSize & sz, bool scale)
{
    wxImage img = bitmap->ConvertToImage();
    delete bitmap;

    if (scale)
    {
        bitmap = new wxBitmap(img.Rescale(sz.x, sz.y, wxIMAGE_QUALITY_NORMAL));
    } else {
        bitmap = new wxBitmap(img.Resize(sz, wxPoint(0,0), 0xFF, 0xFF, 0xFF));
    }

    w = bitmap->GetWidth();
    h = bitmap->GetHeight();

    SetScrollbars(1,1, w, h, 0, 0);
}

void ScrolledWindow::SaveFile(wxString & file)
{
    is_modified = false;
    wxBitmapType type;
    wxString lowFname = file.Lower();

    if (lowFname.EndsWith(_(".bmp")))
        type = wxBITMAP_TYPE_BMP;
    else if (lowFname.EndsWith(_(".png")))
        type = wxBITMAP_TYPE_PNG;
    else if (lowFname.EndsWith(_(".jpg")))
        type = wxBITMAP_TYPE_JPEG;
    else
        type = wxBITMAP_TYPE_BMP;

    bitmap->SaveFile(file, type);
}

void ScrolledWindow::DoCrop()
{
    wxRect d = GetCropRect();

    wxImage img = bitmap->ConvertToImage();
    delete bitmap;

    bitmap = new wxBitmap(img.GetSubImage(d));

    w = bitmap->GetWidth();
    h = bitmap->GetHeight();

    SetScrollbars(1,1, w, h, 0, 0);
}

wxRect ScrolledWindow::GetCropRect()
{
    int x_n1, y_n1, x_n2, y_n2;

    x_n1 = std::min(x1, x2);
    if (x_n1 < 0)
        x_n1 = 0;

    y_n1 = std::min(y1, y2);
    if (y_n1 < 0)
        y_n1 = 0;

    x_n2 = std::max(x1, x2);
    if (x_n2 >= w)
        x_n2 = w;

    y_n2 = std::max(y1, y2);
    if (y_n2 >= w)
        y_n2 = w;

    return wxRect(x_n1, y_n1, x_n2-x_n1, y_n2-y_n1);
}
