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
#include <algorithm>

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
    eFileName,
    eMaxEntry,
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
    void WriteToFile(std::string filename);

    // remove \n
    void removeNewlines(std::string& str);

    template <typename T> 
    std::string stripNewlines(T str) {
        // Find the first non-newline character from the left
        size_t left = str.find_first_not_of('\n');

        // If the string is empty or contains only newlines, return an empty string
        if (left == std::string::npos) {
            return "";
        }

        // Find the last non-newline character from the right
        size_t right = str.find_last_not_of('\n');

        // Extract the substring without leading and trailing newlines
        return str.substr(left, right - left + 1);
    }

    std::string insertAtPositions(int positions[], int size, std::map<EntryType, std::string> fields) {
        std::string finalStr = "";
        int lastPosition = 0;
        if (size > 0) {
            lastPosition = positions[size - 1];
        }

        int which_field = 0;
        EntryType entry;
        bool wrote;
        int i = 0;
        while (i <= lastPosition) {
            wrote = false;
            entry = getEntryType(which_field);

            // iterate over our positions and check if our i is there
            int j = 0;
            while (j < size) {
                if (i == positions[j]) {
                    finalStr += fields[entry];
                    i += fields[entry].size();
                    if (which_field < eMaxEntry) {
                        which_field++;
                        wrote = true;
                        break;
                    }
                }
                j++;
            }
            if (wrote == false) {
                finalStr += " ";
                i++;
            }
        }

        return finalStr;
    }

    EntryType getEntryType(int value) {
        switch (value) {
            case 0: return ePasswordTitle;
            case 1: return ePassword;
            case 2: return eEncryptionLevel;
            case 3: return eFileName;
            case 4: return eMaxEntry;
            default:
                throw std::invalid_argument("Invalid entry type");
        }
}


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

    int fileWritePos[MAX_NUM_ENTRIES] = {0};

    const char* passwordDirPath = "passwordStorage/";

};

#endif //RECORD_PASSWORD_HPP