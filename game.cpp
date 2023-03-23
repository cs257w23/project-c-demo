#include "game.h"

#include <iostream>

#include "cell.h"

using namespace std;

Game::Game(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {
  // The main panel. The root of the component tree.
  root_panel = new wxPanel(this, wxID_ANY);

  // Use a grid layout for the main component.
  wxGridSizer* grid = new wxGridSizer(3, 0, 0);

  // Create the nine subpanels that are the tic-tac-toe board.
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      // Construct GUI components for this space.
      board_panels[row][col] = new Cell(root_panel, this, row, col);
      grid->Add(board_panels[row][col], 1, wxEXPAND | wxALL, 5);

      // Initialize game state for this space.
      state.board[row][col] = PlayerPiece::Empty;
    }
  }
  root_panel->SetSizer(grid);

  // Menu
  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(101, wxT("&New"));
  file->Append(wxID_EXIT, wxT("&Quit"));
  menubar->Append(file, wxT("&File"));
  SetMenuBar(menubar);

  Connect(101, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Game::OnNewGame));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(Game::OnQuit));

  this->Centre();
}

void Game::OccupySpace(int row, int col) {
  assert(state.turn != PlayerPiece::Empty);

  // If the space is occupied, bail.
  if (state.board[row][col] != PlayerPiece::Empty) {
    return;
  }
  board_panels[row][col]->SetPlayer(state.turn);

  state.board[row][col] = state.turn;
  if (state.turn == PlayerPiece::Player1) {
    state.turn = PlayerPiece::Player2;
  } else {
    state.turn = PlayerPiece::Player1;
  }

  if (Winner() != PlayerPiece::Empty) {
    WinnerDialog *dlg = new WinnerDialog(this);
    dlg->ShowModal();
    dlg->Destroy();
    NewGame();
  }
}

void Game::NewGame() {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      state.board[row][col] = PlayerPiece::Empty;
      board_panels[row][col]->SetPlayer(PlayerPiece::Empty);
      state.turn = PlayerPiece::Player1;
    }
  }
}

void Game::OnNewGame(wxCommandEvent& WXUNUSED(event)) { NewGame(); }

void Game::OnQuit(wxCommandEvent& WXUNUSED(event)) { Close(true); }

// Returns PlayerPiece::Empty if there is no winner.
PlayerPiece Game::Winner() const {
  // for each cell check in
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      PlayerPiece base = state.board[row][col];
      if (base == PlayerPiece::Empty) continue;

      for (int row_delta = -1; row_delta <= 1; ++row_delta) {
        int offset_row = row + row_delta;
        int offset_row2 = row + 2 * row_delta;
        if (offset_row < 0 || offset_row > 2) continue;
        if (offset_row2 < 0 || offset_row2 > 2) continue;

        for (int col_delta = -1; col_delta <= 1; ++col_delta) {
          if (col_delta == 0 && row_delta == 0) continue;
          int offset_col = col + col_delta;
          int offset_col2 = col + 2 * col_delta;
          if (col + col_delta < 0 || col + col_delta > 2) continue;
          if (col + 2 * col_delta < 0 || col + 2 * col_delta > 2) continue;

          if (state.board[offset_row][offset_col] == base &&
              state.board[offset_row2][offset_col2] == base) {
            return base;
          }
        }
      }
    }
  }

  return PlayerPiece::Empty;
}
