/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2004 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */
 
#ifndef CDAUDIO_H
#define CDAUDIO_H

#include "common/system.h"

class CDAudio {
public:	
	CDAudio() {
		_isInitialized = false;
		_volumeLevel = 100;
	};

	virtual bool init() = 0;
	virtual void release() = 0;
	
	// OSystem functions
	virtual bool poll() = 0;
	virtual void play(int track, int num_loops, int start_frame, int duration) = 0;
	virtual void stop() = 0;
	virtual void update() = 0;

	// volume in percent
	virtual void setVolume(int volume) { _volumeLevel = volume; }
	virtual int getVolume() { return _volumeLevel; }

	virtual void upVolume(int value) {};
	virtual void downVolume(int value) {};

protected:
	int _volumeLevel;
	bool _isInitialized;
};

#endif