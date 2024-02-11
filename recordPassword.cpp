//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        recordPassword.hpp
// Description: Record password window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "recordPassword.hpp"
#include "entryMenu.hpp"

// constructor
RecordPassword::RecordPassword()
    // there are size and style params here that can be passed to the wxFrame constructor
    : wxFrame(nullptr, wxID_ANY, "Record Password", wxPoint(POS_WINDOW_X,POS_WINDOW_Y), wxSize(SIZE_WINDOW_X,SIZE_WINDOW_Y))
{

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

        // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // text box titles
    wxStaticText* passwordTitle = new wxStaticText(panel, wxID_ANY, "Password title", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    wxStaticText* password = new wxStaticText(panel, wxID_ANY, "Enter password", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+50+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    wxStaticText* encryptionTitle = new wxStaticText(panel, wxID_ANY, "Encryption type", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+100+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    wxStaticText* fileNameTitle = new wxStaticText(panel, wxID_ANY, "File name", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+150+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));

    // text boxes
    wxTextCtrl* tbPasswordTitle = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);
    wxTextCtrl* tbPassword = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX+50), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PASSWORD);
    wxTextCtrl* tbEncryption = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX+100), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);
    wxTextCtrl* tbFileName = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX+150), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);


    // Set font for the static text (optional)
    wxFont font(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD);
    passwordTitle->SetFont(font);
    password->SetFont(font);
    encryptionTitle->SetFont(font);
    fileNameTitle->SetFont(font);

    // Create a backward button
    wxButton* recordButton = new wxButton(panel, wxID_BACKWARD, "Record password", wxPoint(POS_X_BUTTONS, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));
    wxButton* backButton = new wxButton(panel, wxID_BACKWARD, "Back", wxPoint(POS_X_BUTTONS+200, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));

    // Bind a function to handle button click events
    backButton->Bind(wxEVT_BUTTON, &RecordPassword::OnBackButtonClick, this);

    SetMenuBar( menuBar );

}

void RecordPassword::OnBackButtonClick(wxCommandEvent& event) {
    // Open the entry menu frame
    EntryMenu* entryMenu = new EntryMenu();
    entryMenu->Show(true);
    // Close the record password frame
    this->Close();
}