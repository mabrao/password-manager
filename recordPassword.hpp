//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        recordPassword.hpp
// Description: Record password window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RECORD_PASSWORD_HPP
#define RECORD_PASSWORD_HPP

#include <wx/wx.h>

class RecordPassword : public wxFrame
{
public:
    RecordPassword();

private:
    // event handlers
    void OnNew(wxCommandEvent& event);
    void OnBackButtonClick(wxCommandEvent& event);
};

#endif //RECORD_PASSWORD_HPP