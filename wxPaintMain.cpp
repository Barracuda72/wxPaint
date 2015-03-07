/***************************************************************
 * Name:      wxPaintMain.cpp
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

#include "wxPaintMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

wxPaintFrame::wxPaintFrame(wxFrame *frame)
    : GUIFrame(frame)
{
// Workaround
#ifdef WXBLUE_PEN_MISSING
    wxBLUE_PEN = new wxPen(wxColor(0,0,255), 1);
#endif

#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
    ComboInit();
    wxInitAllImageHandlers();

    images = new wxWindowList();

    save = fileMenu->FindChildItem(wxID_SAVE);
    saveAs = fileMenu->FindChildItem(wxID_SAVEAS);
    canvasSize = imageMenu->FindChildItem(ctID_CANVASSIZE);

    SetActiveChild(NULL);

    ToggleStarPanel();

    //wxImageFrame::img_count = 0;

    //wxString test = wxT("/home/barracuda/test.jpg");

    //LoadImage(test);
}

wxPaintFrame::~wxPaintFrame()
{
//    m_mgr->UnInit();
#ifdef WXBLUE_PEN_MISSING
    delete wxBLUE_PEN;
#endif
}

void wxPaintFrame::Dummy(wxString msg = _("none"))
{
    wxMessageBox(wxString::FromUTF8("Dummy: ") << msg);
}

void wxPaintFrame::OnNewFile( wxCommandEvent& event )
{
    //Dummy(_("New"));
    NewImage();
}

void wxPaintFrame::OnOpenFile( wxCommandEvent& event )
{
    wxFileDialog openFileDialog(this, _("Open image"), _(""), _(""),
            _(FILE_MASK), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString fname = openFileDialog.GetPath();
    LoadImage(fname);
    //Dummy(_("Open"));
}

void wxPaintFrame::OnSaveFile( wxCommandEvent& event )
{
    //Dummy(_("Save"));
    wxImageFrame *ac = GetTopImageFrame();
    if (ac != NULL)
    {
        ac->SaveImageFile();
    }
}

void wxPaintFrame::OnSaveFileAs( wxCommandEvent& event )
{
    //Dummy(_("Save As"));
    wxImageFrame *ac = GetTopImageFrame();
    if (ac != NULL)
    {
        ac->SaveImageFileAs();
    }
}

void wxPaintFrame::OnCascadeWindow( wxCommandEvent& event )
{
    //Dummy(_("Cascade"));
    int i,n;
    int x, y, xs, ys;

    n = images->GetCount();

    if (n != 0)
    {
        xs = wxImageFrame::full_header_height;
        ys = wxImageFrame::full_header_height;

        x = 0;
        y = 0;

        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->Move(x,y);
            w->Raise();
            w->DoRefresh();
            x += xs;
            y += ys;
        }
    }
}

void wxPaintFrame::OnLeftToRight( wxCommandEvent& event )
{
    //Dummy(_("Left to Right"));
    int i,n;
    int x, y, xs, ys;

    n = images->GetCount();

    if (n != 0)
    {
        xs = std::max(GetActiveChild()->GetMinSize().x, m_main_panel->GetSize().x/n);
        ys = m_main_panel->GetSize().y;

        x = 0;
        y = 0;

        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->SetSize(xs,ys);
            w->Move(x,y);
            w->Raise();
            w->DoRefresh();
            x += xs;
        }
    }
}

void wxPaintFrame::OnTopToBottom( wxCommandEvent& event )
{
    //Dummy(_("Top to bottom"));
    int i,n;
    int x, y, xs, ys;

    n = images->GetCount();

    if (n != 0)
    {
        xs = m_main_panel->GetSize().x;
        ys = std::max(GetActiveChild()->GetMinSize().y, m_main_panel->GetSize().y/n);

        x = 0;
        y = 0;

        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->SetSize(xs,ys);
            w->Move(x,y);
            w->Raise();
            w->DoRefresh();
            y += ys;
        }
    }
}

void wxPaintFrame::OnTileWindow( wxCommandEvent& event )
{
    //Dummy(_("Tile"));
    int i,n;
    int x, y, xs, ys;
    int maxx = m_main_panel->GetSize().x;

    n = images->GetCount();

    if (n != 0)
    {
        xs = GetActiveChild()->GetMinSize().x;
        ys = GetActiveChild()->GetMinSize().y;

        x = 0;
        y = 0;

        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->SetSize(xs,ys);
            w->Move(x,y);
            w->Raise();
            w->DoRefresh();
            x += xs;
            if (x+xs > maxx)
            {
                x = 0;
                y += ys;
            }
        }
    }
}

void wxPaintFrame::OnMinimizeAll( wxCommandEvent& event )
{
    int i,n;

    n = images->GetCount();

    if (n != 0)
    {
        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->Minimize();
            w->DoRefresh();
        }
    }
}

void wxPaintFrame::OnClose(wxCloseEvent &event)
{
    DoClose();
    Destroy();
}

void wxPaintFrame::OnQuit(wxCommandEvent &event)
{
    DoClose();
    Destroy();
}

void wxPaintFrame::DoClose()
{
    int i,n;

    n = images->GetCount();

    if (n != 0)
    {
        wxWindowList::iterator i;
        wxImageFrame *w;
        for (i = images->begin(); i != images->end(); ++i)
        {
            w = (wxImageFrame *)*i;
            w->SaveImageFile();
            //w->DoRefresh();
        }
    }
}

void wxPaintFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);

    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName(_("wxPaint"));
    aboutInfo.SetVersion(_("v1.0 Beta"));
    aboutInfo.SetDescription(wxString::FromUTF8("My wxWidgets-based paint clone\nPowered by ") << msg);
    aboutInfo.SetCopyright(_("(C) 2015"));
    aboutInfo.SetWebSite(_("http://github.com/Barracuda72/wxPaint"));
    aboutInfo.AddDeveloper(_("Barracuda72 <barracuda72@bk.ru>"));
    wxAboutBox(aboutInfo);
}

void wxPaintFrame::OnCanvasSizeSelected( wxCommandEvent& event )
{
    wxImageFrame *ac = GetTopImageFrame();
    if (ac != NULL)
    {
        ResizeDialog rd(this);
        rd.SetSizeData(ac->GetImageSize(), true);

        if(rd.ShowModal() != wxID_CANCEL)
        {
            wxSize t = rd.GetSizeData();
            ac ->SetCanvasSize(t, rd.GetScaleState());
        }
    }
}

void wxPaintFrame::ComboInit()
{
    // wxFormBuilder does not support comboboxes with images
    // We need to convert standart combo into it
    m_combo_brush = new wxBitmapComboBox(this->m_toolBar, m_choice_brush->GetId(), wxEmptyString,
        m_choice_brush->GetPosition(), m_choice_brush->GetSize(), 0, NULL, wxCB_READONLY);
    int i;
    for (i = 0; i < m_choice_brush->GetCount(); i++)
    {
        m_combo_brush->Append(m_choice_brush->GetString(i));
    }
    m_combo_brush->SetSelection(0);
    this->m_toolBar->DeleteTool(m_choice_brush->GetId());
    m_choice_brush->Destroy();

    this->m_toolBar->InsertControl(0, m_combo_brush);
    m_choice_brush = NULL;

    // Add colored circles
    wxMemoryDC tdc;

    for (i = 0; i < 3; i++)
        DrawPreviewCircle(tdc, i);

    this->Connect(m_combo_brush->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(wxPaintFrame::OnComboSelected));
}

void wxPaintFrame::DrawPreviewCircle(wxMemoryDC & tdc, int n)
{
    wxBitmap *b = new wxBitmap(16, 16);
    tdc.SelectObject(*b);
    // Clear
    tdc.SetPen(*wxWHITE_PEN);
    tdc.SetBrush(*wxWHITE_BRUSH);
    tdc.DrawRectangle(0,0,16,16);

    tdc.SetPen(GetPen(n));
    tdc.SetBrush(GetBrush(n));

    tdc.DrawCircle(8,8, 7);
    //tdc.DrawRectangle(3,3, 9,9);
    tdc.SelectObject(wxNullBitmap);

    m_combo_brush->SetItemBitmap(n, *b);
}

wxPen wxPaintFrame::GetPen(int n)
{
    return wxPen(GetColor(n), m_spinCtrl_brush->GetValue());
}

wxBrush wxPaintFrame::GetBrush(int n)
{
    return wxBrush(GetColor(n));
}

int wxPaintFrame::GetBrushSize()
{
    return m_spinCtrl_brush->GetValue();
}

wxColor wxPaintFrame::GetColor(int n)
{
    switch (n)
    {
        case 0: // Red
            return wxColor(255, 0, 0);

        case 1: // Green
            return wxColor(0, 255, 0);

        case 2: // Blue
            return wxColor(0, 0, 255);

        default:
            return otherColor;
    }
}

void wxPaintFrame::OnComboSelected(wxCommandEvent& event)
{
    if (m_combo_brush->GetSelection() == m_combo_brush->GetCount()-1)
    {
        wxColourDialog c_dialog(this);
        if(c_dialog.ShowModal() != wxID_CANCEL)
        {
            otherColor = c_dialog.GetColourData().GetColour();
            wxMemoryDC tdc;
            DrawPreviewCircle(tdc, m_combo_brush->GetCount()-1);
        }
    }
}

void wxPaintFrame::LoadImage(wxString & name)
{
    wxImageFrame *frame1 = new wxImageFrame(m_main_panel, wxID_ANY, name,
        wxDefaultPosition, wxSize(100, 100), this);

    PostCreate(frame1);
}

void wxPaintFrame::NewImage()
{
    ResizeDialog rd(this);

    rd.SetSizeData(wxSize(640,480), false);

    rd.ShowModal();

    if (rd.IsOk())
    {
        wxImageFrame *frame1 = new wxImageFrame(m_main_panel, wxID_ANY, rd.GetSizeData(),
            wxDefaultPosition, wxSize(100, 100), this);
        PostCreate(frame1);
        //std::cout << "New" << std::endl;
    }
}

void wxPaintFrame::PostCreate(wxImageFrame *f)
{
    f->SetBrushInterface(this);
    /*images->Append(f);

    SetActiveChild(f); // Now done in OnPaint event of wxImageFrame*/

    f->CentreOnParent();
    f->Move(100,100);
    f->Show();
}

wxImageFrame *wxPaintFrame::GetTopImageFrame()
{
    if (images->GetCount() == 0)
        return NULL;
    else if ((activeChild == NULL) || (activeChild->IsBeingDeleted()))
        return NULL;
    else
        return activeChild;
}

wxWindow *wxPaintFrame::GetActiveChild()
{
    return GetTopImageFrame();
}

void wxPaintFrame::SetActiveChild(wxWindow *w)
{
    if (GetActiveChild() != NULL)
    {
        activeChild->isActive = false;
        activeChild->Refresh();
    }

    activeChild = (wxImageFrame *)w;

    if (activeChild == NULL)
    {
        // Try to find available windows
        if (images->GetCount() != 0)
            activeChild = (wxImageFrame *)images->Item(0)->GetData();
    }

    if (GetActiveChild() != NULL)
    {
        activeChild->isActive = true;
        activeChild->DoRefresh(); // Should check here!
    }

    // Enable/disable menu elements
    save->Enable(activeChild != NULL);
    saveAs->Enable(activeChild != NULL);
    canvasSize->Enable(activeChild != NULL);
}

void wxPaintFrame::OnMainPanelUpdate( wxUpdateUIEvent& event )
{
#if 0
    wxWindowList::iterator i;
    wxImageFrame *w;

    for (i = images->begin(); i != images->end(); ++i)
    {
        w = (wxImageFrame *)*i;
        if(!w->IsBeingDeleted())
            w->DoRefresh();
    }

    wxImageFrame *ac = GetTopImageFrame();

    if ((ac != NULL) && (!ac->IsBeingDeleted()))
        ac -> Refresh();
#endif // 1
    //std::cout << "paint!";
}

void wxPaintFrame::RegisterMDIWindow(wxWindow *w)
{
    images->Append(w);
    SetActiveChild(w);
}

void wxPaintFrame::UnregisterMDIWindow(wxWindow *w)
{
    if ((activeChild != NULL) && (w->IsSameAs(*activeChild)))
        SetActiveChild(NULL);

    images->DeleteObject(w);

    if(images->GetCount() == 0)
        SetActiveChild(NULL);
}

int wxPaintFrame::GetStarCorners()
{
    if (m_choice_star->GetSelection() == 0)
        return 0;
    else
        return m_spinCtrl_corners->GetValue();
}

bool wxPaintFrame::IsStarFilled()
{
    return m_checkBox_star->GetValue();
}

void wxPaintFrame::OnStarChoiceChanged( wxCommandEvent& event )
{
    ToggleStarPanel();
}

void wxPaintFrame::ToggleStarPanel()
{
    if(m_choice_star->GetSelection() == 1)
    {
        m_staticText_star->Show();
        m_spinCtrl_corners->Show();
        m_checkBox_star->Show();
    } else {
        m_staticText_star->Hide();
        m_spinCtrl_corners->Hide();
        m_checkBox_star->Hide();
    }
}

bool wxPaintFrame::IsCropActive()
{
    return m_choice_star->GetSelection() == 2;
}
