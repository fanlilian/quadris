#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

class Block : public Subject<Info, State>, public Observer<Info, State> {
	int row, col;
	Shape shape;
  public:
	void setRow(int r);
	void setCol(int c);
	void notify(Subject<Info, State> &whoFrom) override;
	Info getInfo() const override;
	void setShape(Shape shape) override;

};
#endif
