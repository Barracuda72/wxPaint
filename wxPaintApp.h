/***************************************************************
 * Name:      wxPaintApp.h
 * Purpose:   Defines Application Class
 * Author:    Barracuda72 (barracuda72@bk.ru)
 * Created:   2015-03-01
 * Copyright: Barracuda72 (http://lleo.aha.ru/na)
 * License:
 **************************************************************/

#ifndef WXPAINTAPP_H
#define WXPAINTAPP_H

#include <wx/app.h>
#include <wx/minifram.h>
#include <wx/bmpcbox.h>
#include <wx/dcmemory.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <wx/colordlg.h>
#include <wx/scrolwin.h>
#include <wx/image.h>
#include <wx/aboutdlg.h>

#define FILE_MASK "PNG images (*.png)|*.png|BMP images (*.bmp)|*.bmp|JPEG images (*.jpg)|*.jpg;*.jpe;*.jpeg"

#include "ResizeDialog.h"

class wxPaintApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WXPAINTAPP_H
