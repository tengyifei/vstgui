// This file is part of VSTGUI. It is subject to the license terms 
// in the LICENSE file found in the top-level directory of this
// distribution and at http://github.com/steinbergmedia/vstgui/LICENSE

#ifndef __cbuttonstate__
#define __cbuttonstate__

#include "vstguibase.h"

namespace VSTGUI {

//----------------------------
// @brief Button Types (+modifiers)
//----------------------------
enum CButton
{
	/** left mouse button */
	kLButton = 1 << 1,
	/** middle mouse button */
	kMButton = 1 << 2,
	/** right mouse button */
	kRButton = 1 << 3,
	/** shift modifier */
	kShift = 1 << 4,
	/** control modifier (Command Key on Mac OS X and Control Key on Windows) */
	kControl = 1 << 5,
	/** alt modifier */
	kAlt = 1 << 6,
	/** apple modifier (Mac OS X only. Is the Control key) */
	kApple = 1 << 7,
	/** 4th mouse button */
	kButton4 = 1 << 8,
	/** 5th mouse button */
	kButton5 = 1 << 9,
	/** mouse button is double click */
	kDoubleClick = 1 << 10,
	/** system mouse wheel setting is inverted (Only valid for onMouseWheel methods). The distance
	   value is already transformed back to non inverted. But for scroll views we need to know if we
	   need to invert it back. */
	kMouseWheelInverted = 1 << 11
};

//-----------------------------------------------------------------------------
// CButtonState Declaration
//! @brief Button and Modifier state
//-----------------------------------------------------------------------------
struct CButtonState
{
public:
	CButtonState (int32_t state = 0) : state (state) {}
	CButtonState (const CButtonState& bs) : state (bs.state) {}
	
	int32_t getButtonState () const { return state & (kLButton | kRButton | kMButton | kButton4 | kButton5); }
	int32_t getModifierState () const { return state & (kShift | kAlt | kControl | kApple); }

	/** returns true if only the left button is set. Ignores modifier state */
	bool isLeftButton () const { return getButtonState () == kLButton; }
	/** returns true if only the right button is set. Ignores modifier state */
	bool isRightButton () const { return getButtonState () == kRButton; }

	bool isDoubleClick () const { return hasBit<int32_t> (state, kDoubleClick); }

	int32_t operator() () const { return state; }
	CButtonState& operator= (int32_t s) { state = s; return *this; }
	CButtonState& operator&= (int32_t s) { state &= s; return *this; }
	CButtonState& operator|= (int32_t s) { state |= s; return *this; }

	int32_t operator& (const CButtonState& s) const { return state & s.state; }
	int32_t operator| (const CButtonState& s) const { return state | s.state; }
	int32_t operator~ () const { return ~state; }

	bool operator== (const CButtonState& s) const { return state == s.state; }
	bool operator!= (const CButtonState& s) const { return state != s.state; }
protected:
	int32_t state;
};

}

#endif // __cbuttonstate__
