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

    Game *game = new Game(wxT("Tic-tac-toe"));
    game->Show(true);

    return true;
}
