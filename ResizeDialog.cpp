#include "ResizeDialog.h"

ResizeDialog::ResizeDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : ResizeGUI(parent, id, title, pos, size, style)
{
    //ctor
    ok_pressed = false;
}

ResizeDialog::~ResizeDialog()
{
    //dtor
}

void ResizeDialog::OnOkButtonClick( wxCommandEvent& event )
{
    ok_pressed = true;
    w = m_spinCtrl_width->GetValue();
    h = m_spinCtrl_height->GetValue();
    EndModal(wxID_OK);
    this->Close();
}

void ResizeDialog::OnCancelButtonClick( wxCommandEvent& event )
{
    ok_pressed = false;
    w = -1;
    h = -1;
    EndModal(wxID_CANCEL);
    this->Close();
}

wxSize ResizeDialog::GetSizeData()
{
    return wxSize(w,h);
}

void ResizeDialog::SetSizeData(const wxSize & sz, bool scale)
{
    m_spinCtrl_height->SetValue(sz.GetHeight());
    m_spinCtrl_width->SetValue(sz.GetWidth());

    if (scale)
        m_checkBox_scale->Show();
    else
        m_checkBox_scale->Hide();
}

bool ResizeDialog::IsOk()
{
    return ok_pressed;
}

bool ResizeDialog::GetScaleState()
{
    return m_checkBox_scale->GetValue();
}
