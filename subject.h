#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "info.h"
#include "state.h"
#include "observer.h"
#include <vector>
#include <memory>

template <typename InfoType, typename StateType> class Observer;
template <typename InfoType, typename StateType> class Subject{
	std::vector<std::shared_ptr<Observer<InfoType, StateType>> > observers;
	StateType state;
  public:
	void setState(StateType newS);
	void attach(std::shared_ptr<Observer<InfoType, StateType>> observe);
	void detach(std::shared_ptr<Observer<InfoType, StateType>> observe);
	void notifyObserver();
	virtual InfoType getInfo() const = 0;
	StateType getState() const;
	virtual void setShape(Shape shape) = 0;
};
#endif
