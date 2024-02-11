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
    : wxFrame(nullptr, wxID_ANY, "Record Password")
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

    // Create a backward button
    wxButton* backButton = new wxButton(panel, wxID_BACKWARD, "Backward Button", wxPoint(10, 10), wxSize(150, 30));

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