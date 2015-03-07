/***************************************************************
 * Name:      wxImageFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Barracuda72 (barracuda72@bk.ru)
 * Created:   2015-03-01
 * Copyright: Barracuda72 (http://lleo.aha.ru/na)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxImageFrame.h"

BEGIN_EVENT_TABLE(wxImageFrame, wxPanel)
    EVT_CLOSE( wxImageFrame::_OnClose )
    EVT_MOVE( wxImageFrame::_OnMove )
    EVT_LEFT_DOWN( wxImageFrame::_OnMouseDown )
    EVT_LEFT_UP( wxImageFrame::_OnMouseUp )
    EVT_MOTION( wxImageFrame::_OnMouseMove )
    EVT_LEAVE_WINDOW( wxImageFrame::_OnMouseLeave )
    EVT_PAINT( wxImageFrame::_OnPaint )
    EVT_SET_FOCUS( wxImageFrame::_OnSetFocus )
    EVT_KILL_FOCUS( wxImageFrame::_OnKillFocus )
END_EVENT_TABLE()

// Stealed from wxMiniFrame.cpp
// Close button bitmap
const static unsigned char close_bits[] = {
    0xff, 0xff, // 1111111111111111
    0xff, 0xff, // 1111111111111111
    0x07, 0xf0, // 1111000000000111
    0xfb, 0xef, // 1110111111111011
    0xdb, 0xed, // 1110110111011011
    0x8b, 0xe8, // 1110100010001011
    0x1b, 0xec, // 1110110000011011
    0x3b, 0xee, // 1110111000111011
    0x1b, 0xec, // 1110110000011011
    0x8b, 0xe8, // 1110100010001011
    0xdb, 0xed, // 1110110111011011
    0xfb, 0xef, // 1110111111111011
    0x07, 0xf0, // 1111000000000111
    0xff, 0xff, // 1111111111111111
    0xff, 0xff, // 1111111111111111
    0xff, 0xff  // 1111111111111111
};

// Minimize button bitmap
const static unsigned char minimize_bits[] = {
    0xff, 0xff, // 1111111111111111
    0xff, 0xff, // 1111111111111111
    0x07, 0xf0, // 1111000000000111
    0xfb, 0xef, // 1110111111111011
    0xfb, 0xef, // 1110111111111011
    0xfb, 0xef, // 1110111111111011
    0xfb, 0xef, // 1110111111111011
    0xfb, 0xef, // 1110111111111011
    0xfb, 0xef, // 1110111111111011
    0x0b, 0xe8, // 1110100000001011
    0x0b, 0xe8, // 1110100000001011
    0xfb, 0xef, // 1110111111111011
    0x07, 0xf0, // 1111000000000111
    0xff, 0xff, // 1111111111111111
    0xff, 0xff, // 1111111111111111
    0xff, 0xff  // 1111111111111111
};

int wxImageFrame::img_count = 0;

// Create from existing file
wxImageFrame::wxImageFrame(wxWindow *parent, wxWindowID id, const wxString &img, const wxPoint &pos,
            const wxSize &size, BrushInterface *b, long style, const wxString &name)
        : wxPanel(parent, id, pos, size, style, name)
{
    //ctor
    image = new ScrolledWindow(this, wxID_ANY, img);

    filename = img;

    Initialize(parent, b, img);
}

// Create new image
wxImageFrame::wxImageFrame(wxWindow *parent, wxWindowID id, const wxSize &imgsize,
            const wxPoint &pos, const wxSize &size,
            BrushInterface *b,
            long style, const wxString &name)
    : wxPanel(parent, id, pos, size, style, name)
{
    image = new ScrolledWindow(this, wxID_ANY, imgsize);

    filename = wxEmptyString;

    Initialize(parent, b, wxString::FromUTF8("Unsaved - ") << GetImgCount());
}

wxImageFrame::~wxImageFrame()
{
    //dtor
}

void wxImageFrame::Initialize(wxWindow *parent, BrushInterface *i, const wxString & name)
{
    if(!image->IsInitialized())
    {
        wxMessageBox(_("Error loading the image!"));
        Close();
        return;
    }

    image->SetBrushInterface(i);

    //q->SetActiveChild(this);  //FAIL

    dragging = false;
    resizing = false;
    wxImageFrame::parent = parent;
    wxImageFrame::title = name;

    closeBitmap = wxBitmap((const char *)close_bits+2, 14, 14, 1); // 16, 16, depth = 1
    closeBitmap.SetMask(new wxMask(closeBitmap));

    minimizeBitmap = wxBitmap((const char *)minimize_bits+2, 14, 14, 1); // 16, 16, depth = 1
    minimizeBitmap.SetMask(new wxMask(minimizeBitmap));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddSpacer(header_height+6);
    sizer->Add(image, 1, wxALL | wxEXPAND, 1);
    footer = sizer->AddSpacer(footer_height);

    wxSize z = image->GetImageSize();

    //this->SetMaxSize(wxSize(z.GetWidth()+2, z.GetHeight()+header_height+6));
    this->SetMinSize(wxSize(170,100));

    this->SetSizer(sizer);
    this->FitInside();

    is_minimized = false;
}

void wxImageFrame::OnClose( wxCloseEvent& event )
{
    // Cleanup
    SaveImageFile();
    q->UnregisterMDIWindow(this);
    Destroy();
}

void wxImageFrame::OnMouseDown( wxMouseEvent& event )
{
    // Put window to top
    Raise();
    DoRefresh();
    // Set it as toplevel
    q->SetActiveChild(this);

    CaptureMouse();
    x = event.GetX();
    y = event.GetY();

    if (GetCloseRect().Contains(x,y))
    {
        ReleaseMouse();
        this->Close();
    } else if (GetMinimizeRect().Contains(x,y))
    {
        ReleaseMouse();
        if (is_minimized)
            Restore();
        else
            Minimize();
        this->DoRefresh();
    }
    else if (GetHeaderRect().Contains(x, y))
        dragging = true;
    else if (GetResizeRect().Contains(x, y))
        resizing = true;
    else
        ReleaseMouse();
}

void wxImageFrame::OnMouseUp( wxMouseEvent& event )
{
    ReleaseMouse();
    dragging = false;
    resizing = false;
}

void wxImageFrame::OnMouseMove( wxMouseEvent& event )
{
    if(dragging)
    {
        // Move our panel
        wxPoint mouseOnScreen = wxGetMousePosition();
        int newx = mouseOnScreen.x - x;
        int newy = mouseOnScreen.y - y;

        this->Move( parent->ScreenToClient( wxPoint(newx, newy) ) );
    } else if (resizing) {
        this->SetSize(event.GetX(), event.GetY());
        this->DoRefresh();
    } else {
        if (!is_minimized)
        {
            // Set resize cursor, if any
            x = event.GetX();
            y = event.GetY();
            if(GetResizeRect().Contains(x,y))
                this->SetCursor(wxCURSOR_SIZENWSE);
            else
                this->SetCursor(wxNullCursor);
        }
    }
}

void wxImageFrame::OnMouseLeave(wxMouseEvent& event)
{
    // Restore cursor
    this->SetCursor(wxNullCursor);
}

void wxImageFrame::OnPaint(wxPaintEvent& event)
{
    if (!registered)
    {
        registered = true;
        q->RegisterMDIWindow(this);
    }

    wxPaintDC dc(this);

    wxColor orange(255, 128, 0);
    wxColor white(255, 255, 255);
    wxColor grey(180, 180, 180);
    wxColor black(0,0,0);

    // Body & frame
    dc.SetBrush(*wxLIGHT_GREY_BRUSH);
    dc.SetPen(*wxBLACK_PEN);

    if (!is_minimized)
    {
        dc.DrawRectangle(0,0,GetSize().GetWidth(), GetSize().GetHeight());
    } else {
        dc.DrawRectangle(0,0,GetSize().GetWidth(), GetHeaderRect().GetHeight()+border_size*2);
    }

    // Header
    if (isActive)
    {
        dc.SetBrush(wxBrush(orange));
        dc.SetPen(wxPen(orange, 5));
    } else {
        dc.SetBrush(wxBrush(grey));
        dc.SetPen(wxPen(grey, 5));
    }
    dc.DrawRectangle(GetHeaderRect());

    // Title
    if (!title.IsEmpty())
    {
        dc.SetTextForeground(white);
        dc.SetTextBackground(orange);
        if (image->IsModified())
            dc.DrawText(wxString::FromUTF8("* ") << title, border_size, border_size);
        else
            dc.DrawText(title, border_size, border_size);
    }

    // Close button
    /*dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawRectangle(GetCloseRect());*/

    // Close button
    dc.DrawBitmap(closeBitmap, GetCloseRect().x, GetCloseRect().y);

    // Minimize button
    dc.DrawBitmap(minimizeBitmap, GetMinimizeRect().x, GetMinimizeRect().y);

    if (!is_minimized)
    {
        // Footer
        dc.SetTextForeground(black);
        dc.SetTextBackground(black);

        wxSize t = image->GetImageSize();
        wxString isize = wxString::FromUTF8("Width: ") << t.x << wxString::FromUTF8(" | Height: ") << t.y;

        dc.DrawText(isize, GetFooterRect().GetX(), GetFooterRect().GetY()+border_size+3);

        // Resize box
        dc.SetBrush(*wxGREY_BRUSH);
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(GetResizeRect());
    }
}

wxRect wxImageFrame::GetHeaderRect()
{
    int width, height;
    this->GetSize(&width, &height);
    return wxRect(border_size, border_size, width-border_size*2, header_height);
}

wxRect wxImageFrame::GetFooterRect()
{
    int width, height;
    this->GetSize(&width, &height);
    return wxRect(border_size, height-footer_height-border_size*2, width-border_size*2, header_height);
}

wxRect wxImageFrame::GetCloseRect()
{
    int width, height;
    this->GetSize(&width, &height);
    return wxRect(width-border_size-header_height, border_size, header_height, header_height);
}

wxRect wxImageFrame::GetMinimizeRect()
{
    wxRect t = GetCloseRect();
    return wxRect(t.GetX()-header_height, t.GetY(), t.GetWidth(), t.GetHeight());
}

wxRect wxImageFrame::GetResizeRect()
{
    int width, height;
    this->GetSize(&width, &height);
    return wxRect(width-resize_height, height-resize_height, resize_height-2, resize_height-2);
}

void wxImageFrame::SetBrushInterface(BrushInterface *i)
{
    q = i;
}

void wxImageFrame::OnSetFocus( wxFocusEvent& event )
{
   // std::cout << "Focus" << std::endl;
}

void wxImageFrame::OnKillFocus( wxFocusEvent& event )
{
   // std::cout << "Unfocus" << std::endl;
}

void wxImageFrame::DoRefresh()
{
    this->Refresh();
    image->Refresh();

    this->Update();
    image->Update();
    //std::cout << "update" << std::endl;
}

void wxImageFrame::SetCanvasSize(wxSize & sz, bool scale)
{
    image->SetCanvasSize(sz, scale);
    //this->SetMaxSize(wxSize(sz.GetWidth()+2, sz.GetHeight()+header_height+6));
    //this->SetSize(this->GetMaxSize());
    DoRefresh();
}

wxSize wxImageFrame::GetImageSize()
{
    return image->GetImageSize();
}

void wxImageFrame::SaveImageFile()
{
    if(image->IsModified())
    {
        if(filename.IsEmpty())
            SaveImageFileAs();
        else
            image->SaveFile(filename);
    }
}

void wxImageFrame::SaveImageFileAs()
{
    wxString defaultDir = _("");
    wxString defaultFile = _("");
    if (!filename.IsEmpty())
    {
        wxFileName fname(filename);
        defaultDir = fname.GetPath();
        defaultFile = fname.GetFullName();
    }
    //std::cout << defaultDir.ToUTF8().data() << std::endl;
    wxFileDialog saveFileDialog(this, wxString::FromUTF8("Save image: ") << title, defaultDir, defaultFile,
                    _(FILE_MASK), wxFD_SAVE|wxFD_OVERWRITE_PROMPT|wxFD_PREVIEW);

    if (saveFileDialog.ShowModal() != wxID_CANCEL)
    {
        wxString fname = saveFileDialog.GetPath();
        wxString lowFname = fname.Lower();

        // Append extension, if needed
        if (!lowFname.EndsWith(_(".png")) &&
            !lowFname.EndsWith(_(".bmp")) &&
            !lowFname.EndsWith(_(".jpg")))
        {
            switch (saveFileDialog.GetFilterIndex())
            {
                case 0:
                    fname << _(".png");
                    break;
                case 1:
                    fname << _(".bmp");
                    break;
                case 2:
                    fname << _(".jpg");
                    break;
                default:
                    fname << _(".png");
                    break;
            }
        }

        filename = fname;
        title = fname;

        image->SaveFile(filename);

        DoRefresh();
    }
}

void wxImageFrame::Minimize()
{
    is_minimized = true;
    image->Hide();
    footer->Show(false);
}

void wxImageFrame::Restore()
{
    is_minimized = false;
    image->Show();
    footer->Show(true);
}
