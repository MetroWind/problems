#!/usr/bin/env pypy

def rowCol2Coord(row_col, size):
    row, col = row_col
    Result = (col - size//2, size//2 - row)
    return Result

def coord2RowCol(xy, size):
    x, y = xy
    Result = (size//2 - y, x + size//2)
    return Result

def rotate(xy, size):
    x, y = xy
    if size % 2 == 0:
        Result = (y-1, -x)
    else:
        Result = (y, -x)
    return Result

def rotateMatrix(mat):
    Size = len(mat)

    for Offset in range(Size//2):
        for Step in range(0, Size - 2*Offset - 1):
            Row1, Col1 = (Offset, Offset + Step)
            NewRow1, NewCol1 = coord2RowCol(rotate(rowCol2Coord((Row1, Col1), Size), Size), Size)
            Row2, Col2 = (Offset + Step, Size - Offset - 1)
            NewRow2, NewCol2 = coord2RowCol(rotate(rowCol2Coord((Row2, Col2), Size), Size), Size)
            Row3, Col3 = (Size - Offset - 1, Size - Offset - 1 - Step)
            NewRow3, NewCol3 = coord2RowCol(rotate(rowCol2Coord((Row3, Col3), Size), Size), Size)
            Row4, Col4 = (Size - Offset - 1 - Step, Offset)
            NewRow4, NewCol4 = coord2RowCol(rotate(rowCol2Coord((Row4, Col4), Size), Size), Size)

            mat[NewRow1][NewCol1], mat[NewRow2][NewCol2], \
            mat[NewRow3][NewCol3], mat[NewRow4][NewCol4], = \
            mat[Row1][Col1], mat[Row2][Col2], mat[Row3][Col3], mat[Row4][Col4]

