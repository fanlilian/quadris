#include "subject.h"

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS){
	state = newS;
}
template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(std::shared_ptr<Observer<InfoType, StateType>> observe){
	observers.emplace_back(observe);
}
template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::detach(std::shared_ptr<Observer<InfoType, StateType>> observe){
	int i = 0;
	for (auto it : observers){
		if ((it.getInfo().row == observe.getInfo().row) && (it.getInfo().col == observe.getInfo())){
			observers.erase (observers.begin() + i);
		}
		++i;
	}
}
template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObserver(){
	for (auto &observes : observers){
		observes->notify(*this);
	}
}
template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const{
	return state;
}
