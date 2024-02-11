//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        recordPassword.cpp
// Description: Record password window
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>

class RecordPassword : public wxFrame
{
public:
    RecordPassword();

private:
    // event handlers
    void OnNew(wxCommandEvent& event);
};

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

    SetMenuBar( menuBar );


    // CreateStatusBar();
    // SetStatusText(title); // change this?
}