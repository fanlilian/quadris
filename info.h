#ifndef _INFO_H_
#define _INFO_H_
#include <cstddef>
#include <string>
enum class Shape {T, L, J, S, Z, I, O, Empty, Hint};
struct Info {
	int row, col;
	Shape shape;
};
#endif
