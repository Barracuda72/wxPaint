#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include "wxPaintApp.h"
#include "GUIFrame.h"


class ResizeDialog : public ResizeGUI
{
    public:
        ResizeDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Canvas size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 319,133 ), long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~ResizeDialog();
        void SetSizeData(const wxSize & sz, bool scale);
        wxSize GetSizeData();
        bool GetScaleState();
        bool IsOk();

    protected:
        virtual void OnOkButtonClick( wxCommandEvent& event );
		virtual void OnCancelButtonClick( wxCommandEvent& event );
    private:
        unsigned long w, h;
        bool ok_pressed;
};

#endif // RESIZEDIALOG_H
