#include "game.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    GameFrame *game = new GameFrame(wxT("Game"));
    game->Show(true);

    return true;
}
