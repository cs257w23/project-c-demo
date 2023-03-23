#ifndef CELL_H
#define CELL_H

#include "game.h"
#include <wx/wx.h>
#include <wx/bitmap.h>

class Cell : public wxPanel
{
public:
    Cell();
    Cell(wxPanel *parent, BoardGame *game, int row, int col);

    void OnMouseLeftDown(wxMouseEvent &event);
    void SetPlayer(PlayerPiece player);

private:
    // What row am I?
    int row {0};

    // What column am I?
    int col {0};

    // Pointer to the main game.
    BoardGame *game {0};

    wxStaticBitmap *yellow {0};
    wxStaticBitmap *red {0};
};

#endif
