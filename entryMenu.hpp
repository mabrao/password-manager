//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        entryMenu.cpp
// Description: entry menu frame header file.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_HPP

#include <wx/wx.h>

#define VERSION 0.01

// size of window
#define SIZE_ENTRY_WINDOW_X 400
#define SIZE_ENTRY_WINDOW_Y 250

enum
{
    ID_CHANGE_RECORD_PASSWORD_FRAME = 1,
    ID_CHANGE_DECRYPT_FILE_FRAME = 2
};


// declare my entry menu frame
class EntryMenu : public wxFrame
{
public:
    EntryMenu(const wxPoint& position);

private:
    // event handlers
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void ChangeToRecordPassword(wxCommandEvent& event);
    void ChangeToDecryptFile(wxCommandEvent& event);
};


#endif // PASSWORD_MANAGER_HPP