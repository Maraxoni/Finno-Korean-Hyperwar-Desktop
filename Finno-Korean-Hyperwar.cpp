#include <bits/stdc++.h>
#include <string.h>
#include <string>
#include <wx/wx.h>
#include "Files/View.h"


class FKApp : public wxApp {
    wxWindowID id = 1;
    wxString title = "Hyperwar";
    long style;
public:

    bool OnInit() override {
        MainMenu* mainMenu = new MainMenu( nullptr, id, title, wxPoint(100, 100), wxSize(800, 600), style);

        mainMenu->Show(true);

        return true;
    }

};

IMPLEMENT_APP(FKApp)
