#ifndef BRUSHINTERFACE_H
#define BRUSHINTERFACE_H

#include "wxPaintApp.h"

class BrushInterface
{
    public:
        virtual wxPen GetPen() = 0;
        virtual wxBrush GetBrush() = 0;
        virtual int GetBrushSize() = 0;

        virtual void SetActiveChild(wxWindow *) = 0;
        virtual wxWindow *GetActiveChild() = 0;
        virtual void RegisterMDIWindow(wxWindow *w) = 0;
        virtual void UnregisterMDIWindow(wxWindow *w) = 0;

        virtual int GetStarCorners() = 0;
        virtual bool IsStarFilled() = 0;
        virtual bool IsCropActive() = 0;
};

#endif // BRUSHINTERFACE_H
