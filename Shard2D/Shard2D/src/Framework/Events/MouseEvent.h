#pragma once

#include <string>

#include "Event.h"

class EventDispatcher;

class MouseEvent : virtual public Event
{
public:
	MouseEvent() : Event("") { this->_id = "MouseEvent"; };
	MouseEvent(std::string type) { this->_type = type;  this->_id = "MouseEvent"; };

	static const inline std::string LeftButtonPressed				= "leftButtonPressed";
	static const inline std::string LeftButtonReleased				= "leftButtonReleased";

	static const inline std::string RightButtonPressed				= "rightButtonPressed";
	static const inline std::string RightButtonReleased				= "rightButtonReleased";

	static const inline std::string ScrollWheelPressed				= "scrollWheelPressed";
	static const inline std::string ScrollWheelReleased				= "scrollWheelReleased";

	static const inline std::string ScrollWheelUp					= "scrollWheelUp";
	static const inline std::string ScrollWheelDown					= "scrollWheelDown";

	static const inline std::string BeginOverlap					= "beginOverlap";
	static const inline std::string EndOverlap						= "endOverlap";

private:
	friend class EventDispatcher;

	float _mouseX = 0;

	float _mouseY = 0;

public:
	virtual std::string GetID() { return this->_id; };

	float GetMouseX() { return _mouseX; };

	float GetMouseY() { return _mouseY; };
};
