#include "cell.h"

#include <iostream>

#include "game.h"

using namespace std;

Cell::Cell(wxPanel* parent, BoardGame* game, int row, int col)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN),
      game(game),
      row(row),
      col(col) {
  Bind(wxEVT_LEFT_DOWN, &Cell::OnMouseLeftDown, this);

  wxBitmap yellow_bmp = wxBitmap("yellow.png", wxBITMAP_TYPE_PNG);
  wxBitmap red_bmp = wxBitmap("red.png", wxBITMAP_TYPE_PNG);

  yellow = new wxStaticBitmap(this, -1, yellow_bmp);
  red = new wxStaticBitmap(this, -1, red_bmp);
  yellow->Show(false);
  red->Show(false);
}

void Cell::SetPlayer(PlayerPiece player) {
  if (player == PlayerPiece::Player1) {
    yellow->Show(true);
    red->Show(false);
  } else if (player == PlayerPiece::Player2) {
    yellow->Show(false);
    red->Show(true);
  } else {
    yellow->Show(false);
    red->Show(false);
  }
}

void Cell::OnMouseLeftDown(wxMouseEvent& event) {
  game->OccupySpace(row, col);

  if (game->Winner() != PlayerPiece::Empty) {
    WinnerDialog* dlg = new WinnerDialog(this);
    dlg->ShowModal();
    dlg->Destroy();
    game->NewGame();
  }
}
