//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        decrypt.cpp
// Description: Decrypt window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "decrypt.hpp"
#include "entryMenu.hpp"


#define MID_TEXT_BOX_OFFSET 6.25

//pos for text
#define POS_X_TEXT 100
#define START_POS_Y_TEXT 100
//size for text
#define SIZE_TEXT_X 200
#define SIZE_TEXT_Y 50

//pos for text boxes and dropdowns
#define POS_X_BOX 250
#define START_POS_Y_BOX 100
//size for text boxes and dropdowns
#define SIZE_BOX_X 200
#define SIZE_BOX_Y 25

// pos for buttons
#define POS_X_BUTTONS 75
#define POS_Y_BUTTONS 225
//size for buttons
#define SIZE_BUTTONS_X 175
#define SIZE_BUTTONS_Y 30

// constructor
Decrypt::Decrypt(const wxPoint& position)
    // there are size and style params here that can be passed to the wxFrame constructor
    : wxFrame(nullptr, wxID_ANY, "Decrypt", position, wxSize(500, 400))
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

    SetMenuBar( menuBar );

    // Create a panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // text box titles
    wxStaticText* filename = new wxStaticText(panel, wxID_ANY, "Filename", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    wxStaticText* encryptionType = new wxStaticText(panel, wxID_ANY, "Encryption type", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+50+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));

    // Create buttons
    wxButton* backButton = new wxButton(panel, wxID_BACKWARD, "Back", wxPoint(POS_X_BUTTONS, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));
    wxButton* decipherButton = new wxButton(panel, wxID_BACKWARD, "Decipher file", wxPoint(POS_X_BUTTONS+200, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));

    // text boxes
    wxTextCtrl* tbFilename = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);

    // dropdown
    // Array of items for the dropdown
    wxString choices[] = { "Option 1", "Option 2", "Option 3" };

    // Create a dropdown (wxComboBox)
    wxComboBox* dropdown = new wxComboBox(panel, wxID_ANY, wxEmptyString,
                                            wxPoint(POS_X_BOX, START_POS_Y_BOX+50), wxSize(SIZE_BOX_X, SIZE_BOX_Y),
                                            WXSIZEOF(choices), choices,
                                            wxCB_DROPDOWN | wxCB_READONLY);

    // Set an initial selection
    dropdown->SetSelection(0);

    // Set font for the static text (optional)
    wxFont font(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD);
    filename->SetFont(font);
    encryptionType->SetFont(font);

    // bind events for menu
    // Bind(wxEVT_MENU, &EntryMenu::OnNew, this, wxID_NEW);
    // Bind(wxEVT_MENU, &EntryMenu::OnOpen, this, wxID_OPEN);
    // Bind(wxEVT_MENU, &EntryMenu::OnAbout, this, wxID_ABOUT);
    // Bind(wxEVT_MENU, &EntryMenu::OnExit, this, wxID_EXIT);

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
