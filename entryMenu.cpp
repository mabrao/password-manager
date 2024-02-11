//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        entryMenu.cpp
// Description: Entry menu window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "entryMenu.hpp"
#include "recordPassword.hpp"
#include "decrypt.hpp"

// constructor
EntryMenu::EntryMenu()
    // there are size and style params here that can be passed to the wxFrame constructor
    : wxFrame(nullptr, wxID_ANY, "Password Manager")
{

    // main title of application
    wxString title = wxString::Format("Password Manager v%.2f", VERSION);

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->AppendSeparator();
    // stock items: wxID_ABOUT, wxID_EXIT
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a static text control
    wxStaticText* mainTitle = new wxStaticText(panel, wxID_ANY, title, wxPoint(100, 50), wxSize(300, 20));
    // Set font for the static text (optional)
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    mainTitle->SetFont(font);

    // Create buttons
    wxButton* recordNewPassword = new wxButton(panel, ID_CHANGE_RECORD_PASSWORD_FRAME, "Record new password", wxPoint(40, 80), wxSize(150, 30));
    wxButton* decryptFile = new wxButton(panel, ID_CHANGE_DECRYPT_FILE_FRAME, "Decipher file", wxPoint(200, 80), wxSize(150, 30));

    // bind events for menu
    Bind(wxEVT_MENU, &EntryMenu::OnNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &EntryMenu::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &EntryMenu::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &EntryMenu::OnExit, this, wxID_EXIT);

    // bind events for button
    Bind(wxEVT_BUTTON, &EntryMenu::ChangeToRecordPassword, this, ID_CHANGE_RECORD_PASSWORD_FRAME);
    Bind(wxEVT_BUTTON, &EntryMenu::ChangeToDecryptFile, this, ID_CHANGE_DECRYPT_FILE_FRAME);
}

void EntryMenu::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Password Manager v" + std::to_string(VERSION),
                 "About Password Manager", wxOK | wxICON_INFORMATION);
}

void EntryMenu::OnNew(wxCommandEvent& event)
{
    wxLogMessage("I need to implement this function :) Please, try again later");
}

void EntryMenu::OnOpen(wxCommandEvent& event)
{
    wxLogMessage("I need to implement this function :) Please, try again later");
}

void EntryMenu::ChangeToRecordPassword(wxCommandEvent& event) {
    RecordPassword* recordPasswordFrame = new RecordPassword();
    recordPasswordFrame->Show(true);
    // Close the entry menu frame
    this->Close();
}

void EntryMenu::ChangeToDecryptFile(wxCommandEvent& event) {
    Decrypt* decryptFrame = new Decrypt();
    decryptFrame->Show(true);
    // Close the entry menu frame
    this->Close();
}

void EntryMenu::OnExit(wxCommandEvent& event)
{
    Close(true);
}