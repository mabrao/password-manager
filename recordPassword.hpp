//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        recordPassword.hpp
// Description: Record password window.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RECORD_PASSWORD_HPP
#define RECORD_PASSWORD_HPP

#include <wx/wx.h>
#include <iostream>
#include <map>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

// macros with position and size for UI elements

// window pos
#define POS_WINDOW_X 100
#define POS_WINDOW_Y 100
// window size
#define SIZE_WINDOW_X 500
#define SIZE_WINDOW_Y 400

#define MID_TEXT_BOX_OFFSET 6.25

// pos for text titles
#define POS_X_TEXT 100
#define START_POS_Y_TEXT 50
// size for text titles
#define SIZE_TEXT_X 200
#define SIZE_TEXT_Y 50

//pos for text boxes
#define POS_X_BOX 250
#define START_POS_Y_BOX 50
//size for text boxes
#define SIZE_BOX_X 200
#define SIZE_BOX_Y 25

// pos for buttons
#define POS_X_BUTTONS 75
#define POS_Y_BUTTONS 275
//size for buttons
#define SIZE_BUTTONS_X 175
#define SIZE_BUTTONS_Y 30


#define MAX_NUM_ENTRIES 10

enum EntryType {
    ePasswordTitle,
    ePassword,
    eEncryptionLevel,
    eFileName
};

class RecordPassword : public wxFrame
{
public:
    RecordPassword(const wxPoint& position);

private:
    // event handlers
    void OnNew(wxCommandEvent& event);
    void OnBackButtonClick(wxCommandEvent& event);
    void CacheFields(wxCommandEvent& event);

    // writes recorded fields to a file
    void WriteToFile();

    // does file exist
    bool isFile(char* filepath);

    // text box titles
    wxStaticText* passwordTitle;;
    wxStaticText* password;
    wxStaticText* encryptionTitle;
    wxStaticText* fileNameTitle;

    // text boxes
    wxTextCtrl* tbPasswordTitle;
    wxTextCtrl* tbPassword;
    wxTextCtrl* tbFileName;

    //dropdown
    wxComboBox* dropdownEncryption;

    // Array of items for the dropdown
    const wxString encryptionLevels[10] = { "Level 1",
                                           "Level 2",
                                           "Level 3",
                                           "Level 4",
                                           "Level 5",
                                           "Level 6",
                                           "Level 7",
                                           "Level 8",
                                           "Level 9",
                                           "Level 10" };

    std::map<EntryType, std::string> fields;

    uint8_t fileWritePos[MAX_NUM_ENTRIES];

    const char* passwordDirPath = "passwordStorage/";

};

#endif //RECORD_PASSWORD_HPP