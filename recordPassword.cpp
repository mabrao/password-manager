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
RecordPassword::RecordPassword(const wxPoint& position)
    // there are size and style params here that can be passed to the wxFrame constructor
    : wxFrame(nullptr, wxID_ANY, "Record Password", position, wxSize(SIZE_WINDOW_X,SIZE_WINDOW_Y))
{
    // setup top menu
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
    passwordTitle = new wxStaticText(panel, wxID_ANY, "Password title", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    password = new wxStaticText(panel, wxID_ANY, "Enter password", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+50+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    encryptionTitle = new wxStaticText(panel, wxID_ANY, "Encryption type", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+100+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));
    fileNameTitle = new wxStaticText(panel, wxID_ANY, "File name", wxPoint(POS_X_TEXT, START_POS_Y_TEXT+150+MID_TEXT_BOX_OFFSET), wxSize(SIZE_TEXT_X, SIZE_TEXT_Y));

    // text boxes
    tbPasswordTitle = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);
    tbPassword = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX+50), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PASSWORD);
    tbFileName = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(POS_X_BOX, START_POS_Y_BOX+150), wxSize(SIZE_BOX_X, SIZE_BOX_Y), wxTE_PROCESS_ENTER);

    // Create a dropdown (wxComboBox)
    dropdownEncryption = new wxComboBox(panel, wxID_ANY, wxEmptyString,
                                            wxPoint(POS_X_BOX, START_POS_Y_BOX+100), wxSize(SIZE_BOX_X, SIZE_BOX_Y),
                                            WXSIZEOF(encryptionLevels), encryptionLevels,
                                            wxCB_DROPDOWN | wxCB_READONLY);

    // Set an initial selection
    dropdownEncryption->SetSelection(0);


    // Set font for the static text (optional)
    wxFont font(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD);
    passwordTitle->SetFont(font);
    password->SetFont(font);
    encryptionTitle->SetFont(font);
    fileNameTitle->SetFont(font);

    // Create buttons
    wxButton* backButton = new wxButton(panel, wxID_BACKWARD, "Back", wxPoint(POS_X_BUTTONS, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));
    wxButton* recordButton = new wxButton(panel, wxID_BACKWARD, "Record password", wxPoint(POS_X_BUTTONS+200, POS_Y_BUTTONS), wxSize(SIZE_BUTTONS_X, SIZE_BUTTONS_Y));

    // Bind a function to handle button click events
    backButton->Bind(wxEVT_BUTTON, &RecordPassword::OnBackButtonClick, this);
    recordButton->Bind(wxEVT_BUTTON, &RecordPassword::CacheFields, this);

    // Bind functions to handle top menu events
    // Bind(wxEVT_MENU, &EntryMenu::OnNew, this, wxID_NEW);
    // Bind(wxEVT_MENU, &EntryMenu::OnOpen, this, wxID_OPEN);
    // Bind(wxEVT_MENU, &EntryMenu::OnAbout, this, wxID_ABOUT);
    // Bind(wxEVT_MENU, &EntryMenu::OnExit, this, wxID_EXIT);


    // create directory with password files if it doesn't exist
     if (!mkdir(passwordDirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        std::cerr << "Error creating directory!" << std::endl;
    }

}

void RecordPassword::CacheFields(wxCommandEvent& event) {
    //get all fields
    wxString passwordTitle = tbPasswordTitle->GetValue();
    wxString password = tbPassword->GetValue();
    wxString filename = tbFileName->GetValue();
    wxString encryptionLevel = dropdownEncryption->GetStringSelection();

    fields[ePasswordTitle] = passwordTitle.ToStdString();
    fields[ePassword] = password.ToStdString();
    fields[eFileName] = filename.ToStdString();
    fields[eEncryptionLevel] = encryptionLevel.ToStdString();

    WriteToFile();

}

void RecordPassword::WriteToFile() {
    const std::string newEntry = "\n===============================================================================\n";
    std::string fieldsToWrite = "";
    std::string filename;
    uint8_t writePos[MAX_NUM_ENTRIES];
    

    // TODO: look at first entry of file and grab their indexes, if there is no entry, use the tabs
    uint8_t counter = 0;
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        writePos[counter] = sizeof(fieldsToWrite);
        if (it->first == eFileName) {
            filename = it->second;
        }
        if (fileWritePos[counter] != 0) {
            fieldsToWrite.insert(fileWritePos[counter]+sizeof(it->second), it->second);
        } else {
            fieldsToWrite += "\t\t\t" + it->second + "\t\t\t";
        }
        counter++;
    }

    char* cFilename = new char[filename.length() + 1];
    strcpy(cFilename, filename.c_str());

    if (!isFile(cFilename)) {
        std::copy(writePos, writePos + MAX_NUM_ENTRIES, fileWritePos);
    }

    // please add more checks to the password filename
    if (filename.empty()) {
        std::cout << "Please enter a valid file name!" << std::endl;
    }
    
    // Open a file for writing, create if it doesn't exist
    std::string filepath = passwordDirPath + filename;
    std::ofstream outputFile(filepath, std::ios::app);

    if (!outputFile.is_open()) {
        // should this be a pop up window?
        std::cout << "Error opening file for writing!" << std::endl;
    }

    // Write to file
    std::cout << newEntry << std::endl;
    std::cout << "\t\tWriting to file... \t\t" << std::endl;
    std::cout << fieldsToWrite << std::endl;

    outputFile << newEntry << std::endl;
    outputFile << fieldsToWrite << std::endl;


}

void RecordPassword::OnBackButtonClick(wxCommandEvent& event) {
    wxPoint currentPos = GetPosition();
    // Open the entry menu frame
    EntryMenu* entryMenu = new EntryMenu(currentPos);
    entryMenu->Show(true);
    // Close the record password frame
    this->Close();
}

bool RecordPassword::isFile(char* filepath) {
    // access is platform specific (unix)
    return access(filepath, F_OK) == 0;
}