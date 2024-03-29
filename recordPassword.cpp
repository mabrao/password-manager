//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        recordPassword.hpp
// Description: Record password window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "recordPassword.hpp"
#include "entryMenu.hpp"
#include "encrypt.hpp"

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

    WriteToFile(fields[eFileName]);

}

void RecordPassword::WriteToFile(std::string filename) {
    const std::string newEntry = "\n===================================================================================================================================\n";
    std::string autogeneratedMark = "This file was autogenerated by Password Manager.\n";

    // please add more checks to the password filename
    if (filename.empty()) {
        // make this a pop up window
        std::cout << "Please enter a valid file name!" << std::endl;
        return;
    }
    
    // Open a file for reading and writing, create if it doesn't exist
    std::string filepath = passwordDirPath + filename;
    std::fstream outputFile(filepath, std::ios::in | std::ios::out |std::ios::app);

    if (!outputFile.is_open()) {
        // make this a pop window
        std::cout << "Error opening file" << std::endl;
        return;
    }

    // check if the file is empty and if so write the autogeneratedMark
    outputFile.seekg(0, std::ios::end);
    if (outputFile.tellg() == 0) {
        outputFile << autogeneratedMark << std::endl;
    }

    std::string line;
    uint8_t numEntries = 0;
    uint8_t counter = 0;
    bool inField = false;
    bool isFileWritePosZero = true;
    //move cursor to beginning of file
    outputFile.seekg(0, std::ios::beg);
    // Reset fieldWritePos
    std::fill(fileWritePos, fileWritePos + MAX_NUM_ENTRIES, 0);
    // Read all lines from the file
    while (std::getline(outputFile, line)) {
        removeNewlines(autogeneratedMark);
        if (line != autogeneratedMark && counter == 0) {
            // make this a pop up window
            std::cout << "file not autogenerated - cannot write fields to file" << std::endl;
            return;
        }

        // check if all values are zero in our pos array
        isFileWritePosZero = std::all_of(std::begin(fileWritePos), std::end(fileWritePos), [](uint8_t x) { return x == 0; });
        
        // record the positions of the fields on the first line so we write them aligned
        if (isFileWritePosZero) {
            if (line.find(stripNewlines(newEntry)) == std::string::npos && !line.empty() && line.find(stripNewlines(autogeneratedMark)) == std::string::npos) {
                // this is our first line with an entry, record the positions of the fields
                for (int i = 0; i < line.length(); i++) {
                    if ((line[i] != ' ' && line[i] != '\t' && line[i] != '\n') && !inField) {
                        // found our first entry and the first position for the field
                        memcpy(&fileWritePos[numEntries], &i, sizeof(i));
                        numEntries++;
                        inField = true;
                    } else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
                        inField = false;
                    }
                }
                isFileWritePosZero = false;
                break;
            }
        } else {
            // we already have our positions, let's break
            isFileWritePosZero = false;
            break;
        }
        counter++;
    }

    std::string fieldsToWrite;
    std::string encrypted_password = Encrypt::encryptString(fields[eEncryptionLevel], fields[ePassword]);
    fields[ePassword] = encrypted_password;
    if (isFileWritePosZero) {
        fieldsToWrite = "          " + fields[ePasswordTitle] + "          " + fields[ePassword] + "          " + fields[eEncryptionLevel] + "          " + fields[eFileName] + "          ";
    } else {
        fieldsToWrite = insertAtPositions(fileWritePos, numEntries, fields);
    }

    std::cout << "\nPassword decrypted = "<< Encrypt::encryptString(fields[eEncryptionLevel], fields[ePassword], true) << "\n" << std::endl;

    // Write to file
    std::cout << newEntry << std::endl;
    std::cout << "Writing to file " + filename << std::endl;
    std::cout << fieldsToWrite << std::endl;

    // Flush the stream to ensure data is written
    outputFile.flush();
    // Close the file before reopening
    outputFile.close();
    // Reopen the file for writing (creates a new std::fstream object)
    std::fstream outputFileReopen(filepath, std::ios::out | std::ios::app);

    if (outputFileReopen.fail()) {
        std::cout << "Error writing to file" << std::endl;
        return;
    }

    outputFileReopen << newEntry << std::endl;
    outputFileReopen << fieldsToWrite << std::endl;

    outputFileReopen.close();

}

void RecordPassword::OnBackButtonClick(wxCommandEvent& event) {
    wxPoint currentPos = GetPosition();
    // Open the entry menu frame
    EntryMenu* entryMenu = new EntryMenu(currentPos);
    entryMenu->Show(true);
    // Close the record password frame
    this->Close();
}

// bool RecordPassword::isFile(char* filepath) {
//     // access is platform specific (unix)
//     return access(filepath, F_OK) == 0;
// }

void RecordPassword::removeNewlines(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}