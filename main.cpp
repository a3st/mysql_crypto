// github.com/A3st76/mysql_crypto. Source file under MIT license.

#include "frame.h"
#include "global.h"

std::unique_ptr<DatabaseHandler> g_database_handler;
std::unique_ptr<DataMiner> g_data_miner;

bool MyApp::OnInit()
{
   /* FILE* fDummy;
    ::AllocConsole();

    ::freopen_s(&fDummy, "CONIN$", "r", stdin);
    ::freopen_s(&fDummy, "CONOUT$", "w", stderr);
    ::freopen_s(&fDummy, "CONOUT$", "w", stdout);
    */

    if (!wxApp::OnInit()) {
        return false;
    }

    MyFrame1* frame = new MyFrame1(wxT("CryptoAnalytics")
#ifndef __WXWINCE__
        , wxPoint(50, 50), wxSize(971, 820)
#endif
    );

    g_database_handler = std::make_unique<DatabaseHandler>();
    g_data_miner = std::make_unique<DataMiner>();

    frame->Show(true);
    return true;
}

int MyApp::OnExit() {
    return wxApp::OnExit();
}

IMPLEMENT_APP(MyApp)