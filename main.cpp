//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        main.cpp
// Description: A simple password manager with the purpose of learning the wxWidgets library.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <wx/wx.h>
#include "entryMenu.hpp"

// declare app entry point
class PasswordManager : public wxApp
{
public:
    bool OnInit() override;
};


// all window objects are destroyed when the correspondent
// on-screen window is destroyed
// all windows MUST not be deleted by the application
bool PasswordManager::OnInit()
{
    EntryMenu *frame = new EntryMenu();
    frame->Show(true);
    return true;
}


// macro that defines the entry point of the application
wxIMPLEMENT_APP(PasswordManager);