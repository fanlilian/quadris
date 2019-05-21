#ifndef _PIECE_STATE_H_
#define _PIECE_STATE_H_

enum class PieceType {Placed, New, Changing, Dropping};
struct pieceState{
	PieceType piece;
};
#endif
