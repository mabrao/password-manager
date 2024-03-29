//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        decrypt.hpp
// Description: Decrypt window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DECRYPT_HPP
#define DECRYPT_HPP

#include <wx/wx.h>

// forward declaration of EntryMenu
// class EntryMenu;

class Decrypt : public wxFrame
{
public:
    Decrypt(const wxPoint& position);

private:
    // event handlers
    // void OnNew(wxCommandEvent& event);
    // void OnOpen(wxCommandEvent& event);
    // void OnExit(wxCommandEvent& event);
    // void OnAbout(wxCommandEvent& event);

    void OnBackButtonClick(wxCommandEvent& event);
};

#endif // DECRYPT_HPP