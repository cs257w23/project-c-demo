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

    Game *game = new Game(wxT("Game"));
    game->Show(true);

    return true;
}
