#include "game.h"

#include <iostream>

#include "cell.h"

using namespace std;

GameFrame::GameFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {
  // The main panel. The root of the component tree.
  root_panel = new wxPanel(this, wxID_ANY);

  // Menu
  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(101, wxT("&New Tic-tac-toe game"));
  file->Append(102, wxT("&New Connect 4 game"));
  file->Append(wxID_EXIT, wxT("&Quit"));
  menubar->Append(file, wxT("&File"));
  SetMenuBar(menubar);

  Connect(101, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(GameFrame::OnNewTTGame));
  Connect(102, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(GameFrame::OnNewC4Game));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(GameFrame::OnQuit));

  wxGridSizer* grid = new wxGridSizer(1, 0, 0);

  root_panel->SetSizer(grid);
  this->Centre();
}

BoardGame::BoardGame(wxPanel* parent, int rows, int cols)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
  // Use a grid layout for the main component.
  wxGridSizer* grid = new wxGridSizer(cols, 0, 0);

  // Create the subpanels that are the game board.
  for (int row = 0; row < rows; ++row) {
    vector<Cell*> panel_row_vec;
    vector<PlayerPiece> state_row_vec;
    for (int col = 0; col < cols; ++col) {
      // Construct GUI components for this space.
      panel_row_vec.push_back(new Cell(this, this, row, col));
      grid->Add(panel_row_vec.back(), 1, wxEXPAND | wxALL, 5);

      // Initialize game state for this space.
      state_row_vec.push_back(PlayerPiece::Empty);
    }

    board_panels.push_back(panel_row_vec);
    state.board.push_back(state_row_vec);
  }
  this->SetSizer(grid);
}

void BoardGame::OccupySpace(int row, int col) {
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
}

void BoardGame::NewGame() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      state.board[row][col] = PlayerPiece::Empty;
      board_panels[row][col]->SetPlayer(PlayerPiece::Empty);
      state.turn = PlayerPiece::Player1;
    }
  }
}

void GameFrame::OnNewTTGame(wxCommandEvent& WXUNUSED(event)) {
  // Destroy any previous tic-tac-toe games or connect4 games. 
  // Destroy is a method provided by wxWidgets.
  if (tt_game)  {
    tt_game->Destroy();
    tt_game = 0;
  }
  if (c4_game)  {
    c4_game->Destroy();
    c4_game = 0;
  }

  // Create a new TicTacToe game and add it to the root panel.
  // Expand it to fill the entire panel.
  tt_game = new TicTacToeGame(root_panel);
  root_panel->GetSizer()->Add(tt_game, 1, wxEXPAND | wxALL, 0);

  // We have removed and added components, so we need to reflow the layout.
  root_panel->Layout();
  tt_game->Show(true);
}

void GameFrame::OnNewC4Game(wxCommandEvent& WXUNUSED(event)) {
  // Destroy any previous tic-tac-toe games or connect4 games. 
  // Destroy is a method provided by wxWidgets.
  if (tt_game)  {
    tt_game->Destroy();
    tt_game = 0;
  }
  if (c4_game)  {
    c4_game->Destroy();
    c4_game = 0;
  }

  // Create a new Connect4 game and add it to the root panel.
  // Expand it to fill the entire panel.
  c4_game = new Connect4Game(root_panel);
  root_panel->GetSizer()->Add(c4_game, 1, wxEXPAND | wxALL, 0);

  // We have removed and added components, so we need to reflow the layout.
  root_panel->Layout();
  c4_game->Show(true);
}

void GameFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) { Close(true); }

// Returns PlayerPiece::Empty if there is no winner.
PlayerPiece TicTacToeGame::Winner() const {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
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
// Returns PlayerPiece::Empty if there is no winner.
PlayerPiece Connect4Game::Winner() const {
  return PlayerPiece::Empty;
}
