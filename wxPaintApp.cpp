/***************************************************************
 * Name:      wxPaintApp.cpp
 * Purpose:   Code for Application Class
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

#include "wxPaintApp.h"
#include "wxPaintMain.h"

IMPLEMENT_APP(wxPaintApp);

bool wxPaintApp::OnInit()
{
    wxPaintFrame* frame = new wxPaintFrame(0L);
    
    frame->Show();
    
    return true;
}
