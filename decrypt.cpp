//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        decrypt.cpp
// Description: Decrypt window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "decrypt.hpp"
#include "entryMenu.hpp"

// constructor
Decrypt::Decrypt(const wxPoint& position)
    // there are size and style params here that can be passed to the wxFrame constructor
    : wxFrame(nullptr, wxID_ANY, "Decrypt", position, wxSize(500, 400))
{

    // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create a backward button
    wxButton* backButton = new wxButton(panel, wxID_BACKWARD, "Backward Button", wxPoint(10, 10), wxSize(150, 30));

    // Bind a function to handle button click events
    backButton->Bind(wxEVT_BUTTON, &Decrypt::OnBackButtonClick, this);

}

void Decrypt::OnBackButtonClick(wxCommandEvent& event) {
    wxPoint currentPos = GetPosition();
    // Open the entry menu frame
    EntryMenu* entryMenu = new EntryMenu(currentPos);
    entryMenu->Show(true);
    // Close the decrypt frame
    this->Close();

}
