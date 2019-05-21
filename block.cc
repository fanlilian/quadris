#include "block.h"

void Block::setRow(int r){// setter for a block row
	row = r;                 // set block row to r
}

void Block::setCol(int c){    // setter for a block column
	col = c;                                                                        // set block col to c
}

void Block::notify(Subject<Info, State> &whoFrom){                       // notified by my subject
	if (whoFrom.getState().type == StateType::Clear){	// If whoFrom signals clear
		if (whoFrom.getInfo().row == row){	// Check if it's in the same row
		  State clear;
			clear.type = StateType::Clear;
			setState(clear);	// if same row and set state to clear (no swap)
		}
		else{					// else a swap must be made
			whoFrom.setShape(shape);	// swapping changing shape
			State copy;
			copy.type = StateType::Copy;
			setState(copy);	// I need to copy your shape
		}
	}

	else {
		State copy;
		copy.type = StateType::Copy;
		setState(copy);		// I need to copy your shape
	}
	notify(*this);
}

void Block::setShape(Shape shape){	                                            // setter for a block's colour
	Block::shape = shape;                                                          // set block shape to shape
}

Info Block::getInfo() const{    	                                            // getter for a block's info
	Info i;                                                                         // create an info object
	i.row = row;                                                                    // set info's row field to block's row
	i.col = col;                                                                    // set info's col field to block's col
	i.shape = shape;                                                                // set info's shape field to block's shape
	return i;                                                                       // return the infor object.
}
