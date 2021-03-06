/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifdef ENABLE_EOB

#include "kyra/darkmoon.h"
#include "kyra/screen_eob.h"
#include "kyra/resource.h"
#include "kyra/sound.h"

#include "common/system.h"

#include "base/version.h"

namespace Kyra {

class DarkmoonSequenceHelper {
friend class DarkMoonEngine;
public:
	enum Mode {
		kIntro,
		kFinale
	};

	DarkmoonSequenceHelper(OSystem *system, DarkMoonEngine *vm, Screen_EoB *screen, Mode mode, const char *const *strings, const char *const *cpsFiles, const char *const *palFiles, const EoBShapeDef **shapeDefList, const EoBSequenceStep **seqList);
	~DarkmoonSequenceHelper();

	void loadScene(int index, int pageNum);
	void runSequence(int index, int del = -1);

	void printText(int index, int color);
	void fadeText();

	void update(int srcPage);

	void setPalette(int index);
	void fadePalette(int index, int del);
	void copyPalette(int srcIndex, int destIndex);

	void initDelayedPaletteFade(int palIndex, int rate);
	bool processDelayedPaletteFade();

	void delay(uint32 ticks);
	void waitForSongNotifier(int index, bool introUpdateAnim = false);

private:
	void setPaletteWithoutTextColor(int index);

	OSystem *_system;
	DarkMoonEngine *_vm;
	Screen_EoB *_screen;
	Mode _mode;

	const char *const *_strings;
	const char *const *_cpsFiles;
	const char *const *_palFiles;
	const EoBShapeDef **_shapeDefs;
	const EoBSequenceStep **_seqData;

	Palette *_palettes[12];

	const uint8 **_shapes;

	uint32 _fadePalTimer;
	int _fadePalRate;
	int _fadePalIndex;
};

int DarkMoonEngine::mainMenu() {
	int menuChoice = _menuChoiceInit;
	_menuChoiceInit = 0;

	_sound->loadSoundFile("INTRO");
	Screen::FontId of = _screen->_currentFont;
	int op = 0;
	Common::SeekableReadStream *s = 0;

	while (menuChoice >= 0 && !shouldQuit()) {
		switch (menuChoice) {
		case 0: {
			s = _res->createReadStream("XENU.CPS");
			if (s) {
				s->read(_screen->getPalette(0).getData(), 768);
				_screen->loadFileDataToPage(s, 3, 64000);
				delete s;
			} else {
				_screen->loadBitmap("MENU.CPS", 3, 2, &_screen->getPalette(0));
			}

			_screen->setScreenPalette(_screen->getPalette(0));

			of = _screen->setFont(Screen::FID_6_FNT);
			op = _screen->setCurPage(2);
			Common::String versionString(Common::String::format("ScummVM %s", gScummVMVersion));
			_screen->printText(versionString.c_str(), 267 - versionString.size() * 6, 160, 13, 0);
			_screen->setFont(of);
			_screen->_curPage = op;
			_screen->copyRegion(0, 0, 0, 0, 320, 200, 2, 0, Screen::CR_NO_P_CHECK);
			_screen->updateScreen();
			menuChoice = mainMenuLoop();
		} break;

		case 1:
			// load game in progress
			menuChoice = -1;
			break;

		case 2:
			// create new party
			menuChoice = -2;
			break;

		case 3:
			// transfer party
			//seq_playFinale();
			menuChoice = -3;
			break;

		case 4:
			// play intro
			seq_playIntro();
			menuChoice = 0;
			break;

		case 5:
			// quit
			menuChoice = -5;
			break;
		}
	}

	return shouldQuit() ? -5 : menuChoice;
}

int DarkMoonEngine::mainMenuLoop() {
	int sel = -1;
	do {
		_screen->setScreenDim(6);
		_gui->simpleMenu_setup(6, 0, _mainMenuStrings, -1, 0, 0);

		while (sel == -1 && !shouldQuit())
			sel = _gui->simpleMenu_process(6, _mainMenuStrings, 0, -1, 0);
	} while ((sel < 0 || sel > 5) && !shouldQuit());

	return sel + 1;
}

void DarkMoonEngine::seq_playIntro() {
	DarkmoonSequenceHelper sq(_system, this, _screen, DarkmoonSequenceHelper::kIntro, _introStrings, _cpsFilesIntro, _palFilesIntro, _shapesIntro, _seqIntro);

	_screen->setCurPage(0);
	_screen->clearCurPage();

	snd_stopSound();

	sq.loadScene(4, 2);
	sq.loadScene(0, 2);
	sq.delay(1);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);

	_screen->copyRegion(0, 0, 8, 8, 304, 128, 2, 0, Screen::CR_NO_P_CHECK);
	sq.setPalette(9);
	sq.fadePalette(0, 3);

	_screen->setCurPage(2);
	_screen->setClearScreenDim(17);
	_screen->setCurPage(0);

	removeInputTop();
	sq.delay(18);

	sq.runSequence(3, 18);
	sq.runSequence(6, 18);
	sq.runSequence(0);

	sq.waitForSongNotifier(1);

	sq.runSequence(11);
	sq.runSequence(7, 6);
	sq.runSequence(2, 6);

	sq.waitForSongNotifier(2);

	sq.runSequence(38);
	sq.runSequence(3);
	sq.runSequence(8);
	sq.runSequence(1, 10);
	sq.runSequence(0, 6);
	sq.runSequence(2);

	sq.waitForSongNotifier(3);

	_screen->setClearScreenDim(17);
	_screen->setCurPage(2);
	_screen->setClearScreenDim(17);
	_screen->setCurPage(0);

	sq.runSequence(40);
	sq.runSequence(7, 18);

	sq.printText(0, 16);    // You were settling...
	sq.runSequence(7, 90);
	sq.fadeText();

	sq.printText(1, 16);    // Then a note was slipped to you
	sq.runSequence(8);
	sq.runSequence(2, 72);
	sq.fadeText();

	sq.printText(2, 16);    // It was from your friend Khelben Blackstaff...
	sq.runSequence(2);
	sq.runSequence(6, 36);
	sq.runSequence(3);
	sq.fadeText();

	sq.printText(3, 16);    // The message was urgent.

	sq.loadScene(1, 2);
	sq.waitForSongNotifier(4);

	// intro scroll
	if (!skipFlag() && !shouldQuit()) {
		for (int i = 0; i < 280; i += 3) {
			uint32 endtime = _system->getMillis() + _tickLength;
			_screen->copyRegion(11, 8, 8, 8, 301, 128, 0, 0, Screen::CR_NO_P_CHECK);
			_screen->copyRegion(i, 0, 309, 8, 3, 128, 2, 0, Screen::CR_NO_P_CHECK);
			_screen->updateScreen();
			if (i == 96)
				sq.runSequence(42);
			delayUntil(endtime);
		}
	}

	_screen->copyRegion(8, 8, 0, 0, 304, 128, 0, 2, Screen::CR_NO_P_CHECK);
	sq.runSequence(4);
	sq.fadeText();
	sq.delay(10);

	sq.loadScene(2, 2);
	sq.update(2);
	sq.delay(10);

	sq.printText(4, 16);    // What could Khelben want?
	sq.delay(25);

	sq.loadScene(3, 2);
	sq.delay(54);
	sq.runSequence(13);
	_screen->copyRegion(104, 16, 96, 8, 120, 100, 0, 2, Screen::CR_NO_P_CHECK);
	sq.fadeText();

	sq.printText(5, 15);    // Welcome, please come in
	sq.runSequence(10);
	sq.runSequence(10);
	sq.runSequence(9);
	sq.runSequence(9);
	sq.fadeText();

	sq.printText(6, 15);    // Khelben awaits you in his study
	for (int i = 0; i < 3; i++)
		sq.runSequence(10);
	sq.runSequence(9);
	sq.runSequence(14);
	sq.loadScene(5, 2);

	sq.waitForSongNotifier(5);

	sq.fadeText();
	_screen->clearCurPage();
	_screen->updateScreen();

	for (int i = 0; i < 6; i++)
		sq.runSequence(15);

	sq.loadScene(6, 2);
	sq.loadScene(7, 2);
	_screen->clearCurPage();
	sq.update(2);

	sq.runSequence(16);
	sq.printText(7, 15);    // Thank you for coming so quickly
	sq.runSequence(16);
	sq.runSequence(17);
	for (int i = 0; i < 3; i++)
		sq.runSequence(16);
	sq.fadeText();
	sq.runSequence(16);

	sq.loadScene(8, 2);
	sq.update(2);
	sq.runSequence(32);
	sq.printText(8, 15);    // I am troubled my friend
	sq.runSequence(33);
	sq.runSequence(33);
	for (int i = 0; i < 4; i++)
		sq.runSequence(32);
	sq.fadeText();

	sq.printText(9, 15);    // Ancient evil stirs in the Temple Darkmoon
	sq.runSequence(33);
	sq.runSequence(43);
	sq.runSequence(33);
	for (int i = 0; i < 3; i++)
		sq.runSequence(32);
	sq.fadeText();

	sq.printText(10, 15);   // I fear for the safety of our city
	for (int i = 0; i < 4; i++)
		sq.runSequence(33);
	sq.runSequence(32);
	sq.runSequence(32);

	sq.loadScene(9, 2);
	sq.fadeText();

	sq.waitForSongNotifier(6);

	sq.update(2);
	sq.runSequence(34);

	sq.printText(11, 15);   // I need your help
	for (int i = 0; i < 3; i++)
		sq.runSequence(34);
	sq.runSequence(35);
	for (int i = 0; i < 4; i++)
		sq.runSequence(34);
	sq.fadeText();

	sq.loadScene(12, 2);
	sq.update(2);
	sq.loadScene(6, 2);
	sq.runSequence(18);

	sq.printText(12, 15);   // Three nights ago I sent forth a scout
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(22);
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(18);
	sq.fadeText();

	sq.printText(13, 15);   // She has not yet returned
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(23);
	sq.runSequence(24);
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(17);
	sq.runSequence(18);
	sq.fadeText();

	sq.printText(14, 15);   // I fear for her safety
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(20);
	sq.runSequence(18);
	sq.runSequence(25);
	sq.runSequence(18);
	sq.runSequence(18);
	sq.fadeText();
	sq.runSequence(18);
	sq.runSequence(18);

	sq.printText(15, 15);   // Take this coin
	sq.runSequence(28);
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(18);
	sq.runSequence(18);
	sq.fadeText();

	sq.loadScene(10, 2);
	_screen->clearCurPage();
	_screen->updateScreen();

	sq.runSequence(37, 18);
	sq.runSequence(36, 36);

	sq.loadScene(12, 2);
	_screen->clearCurPage();
	sq.update(2);

	sq.loadScene(11, 2);
	sq.printText(16, 15);   // I will use it to contact you
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(20);
	sq.runSequence(18);
	sq.runSequence(18);
	sq.fadeText();

	sq.printText(17, 15);   // You must act quickly
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(18);
	sq.runSequence(18);
	sq.fadeText();
	sq.runSequence(18);

	sq.printText(18, 15);   // I will teleport you near Darkmoon
	sq.runSequence(20);
	sq.runSequence(27);
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(18);
	sq.runSequence(18);
	sq.fadeText();
	sq.runSequence(18);

	sq.printText(19, 15);   // May luck be with you my friend
	sq.runSequence(19);
	sq.runSequence(19);
	sq.runSequence(20);
	sq.runSequence(18);
	sq.fadeText();
	sq.runSequence(29);

	sq.waitForSongNotifier(7);

	sq.runSequence(30);
	sq.runSequence(31);

	sq.waitForSongNotifier(8, true);

	if (skipFlag() || shouldQuit()) {
		_sound->playTrack(15);
	} else {
		_screen->setScreenDim(17);
		_screen->clearCurDim();
		_sound->playTrack(14);
		sq.fadePalette(10, 1);
		_screen->setClearScreenDim(18);
		sq.delay(6);
		sq.fadePalette(9, 1);
		_screen->clearCurPage();
	}

	sq.fadePalette(9, 10);
}

void DarkMoonEngine::seq_playFinale() {
	DarkmoonSequenceHelper sq(_system, this, _screen, DarkmoonSequenceHelper::kFinale, _finaleStrings, _cpsFilesFinale, _palFilesFinale, _shapesFinale, _seqFinale);

	_screen->setCurPage(0);
	_screen->setFont(Screen::FID_8_FNT);

	_sound->loadSoundFile("FINALE1");
	snd_stopSound();
	sq.delay(3);

	_screen->clearCurPage();
	_screen->updateScreen();

	sq.loadScene(0, 2);
	sq.delay(18);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(1);
	sq.update(2);

	sq.loadScene(1, 2);

	sq.runSequence(0);
	sq.runSequence(0);
	for (int i = 0; i < 3; i++)
		sq.runSequence(2);
	sq.runSequence(1);
	sq.runSequence(2);
	sq.runSequence(2);

	sq.printText(0, 10);            // Finally, Dran has been defeated
	for (int i = 0; i < 7; i++)
		sq.runSequence(2);
	sq.fadeText();
	sq.runSequence(2);

	sq.waitForSongNotifier(1);

	sq.printText(1, 10);            // Suddenly, your friend Khelben appears
	sq.runSequence(4);
	for (int i = 0; i < 3; i++)
		sq.runSequence(2);
	sq.fadeText();

	sq.printText(2, 15);            // Greetings, my victorious friends
	for (int i = 0; i < 4; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();
	sq.runSequence(6);

	sq.printText(3, 15);            // You have defeated Dran
	for (int i = 0; i < 5; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.printText(4, 15);            // I did not know Dran was a dragon
	for (int i = 0; i < 4; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.printText(5, 15);            // He must have been over 300 years old
	for (int i = 0; i < 4; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.printText(6, 15);            // His power is gone
	for (int i = 0; i < 3; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.printText(7, 15);            // But Darkmoon is still a source of great evil
	for (int i = 0; i < 4; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.printText(8, 15);            // And many of his minions remain
	for (int i = 0; i < 4; i++)
		sq.runSequence(5);
	sq.runSequence(2);
	sq.runSequence(2);
	sq.fadeText();

	sq.loadScene(2, 2);
	sq.update(2);
	sq.loadScene(3, 2);
	_screen->copyRegion(8, 8, 0, 0, 304, 128, 0, 2, Screen::CR_NO_P_CHECK);

	sq.printText(9, 15);            // Now we must leave this place
	sq.runSequence(7);
	sq.runSequence(8);
	sq.runSequence(7);
	sq.runSequence(7, 36);
	sq.fadeText();

	sq.printText(10, 15);           // So my forces can destroy it..
	for (int i = 0; i < 3; i++)
		sq.runSequence(7);
	sq.runSequence(8);
	sq.runSequence(7);
	sq.runSequence(7, 36);
	sq.runSequence(8, 18);
	sq.fadeText();

	sq.printText(11, 15);           // Follow me
	sq.runSequence(7, 18);
	sq.runSequence(9, 18);
	sq.runSequence(8, 18);
	sq.fadeText();

	sq.loadScene(7, 2);
	sq.copyPalette(3, 0);
	sq.loadScene(4, 2);

	sq.waitForSongNotifier(2);

	_screen->clearCurPage();
	sq.update(2);

	sq.loadScene(8, 2);
	sq.loadScene(6, 6);
	sq.delay(10);

	sq.printText(12, 10);           // Powerful mages stand ready for the final assault...
	sq.delay(90);
	sq.fadeText();

	sq.waitForSongNotifier(3);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(7);
	sq.delay(8);

	sq.runSequence(10);
	sq.runSequence(13);
	sq.initDelayedPaletteFade(4, 1);

	sq.runSequence(14);
	sq.runSequence(13);
	sq.runSequence(14);
	sq.runSequence(14);
	sq.runSequence(13);
	sq.initDelayedPaletteFade(2, 1);

	sq.runSequence(15);
	sq.runSequence(14);
	sq.runSequence(13);
	sq.runSequence(15);
	sq.runSequence(15);
	sq.runSequence(11);

	sq.printText(13, 10);           // The temple's evil is very strong
	sq.delay(72);
	sq.fadeText();

	sq.printText(14, 10);           // It must not be allowed...
	sq.delay(72);
	sq.fadeText();

	sq.waitForSongNotifier(4);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(7);
	sq.delay(8);

	sq.runSequence(10);
	sq.initDelayedPaletteFade(5, 1);
	sq.runSequence(13);
	sq.runSequence(14);
	sq.runSequence(13);
	sq.runSequence(14);
	sq.runSequence(13);
	sq.runSequence(13);
	sq.runSequence(14);
	sq.runSequence(14);
	sq.runSequence(13);
	sq.runSequence(12);
	for (int i = 0; i < 4; i++)
		sq.runSequence(16);
	sq.runSequence(17);
	sq.runSequence(18);

	sq.printText(15, 10);           // The temple ceases to exist
	sq.initDelayedPaletteFade(6, 1);
	sq.delay(36);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);

	sq.delay(54);
	sq.fadeText();
	sq.loadScene(12, 2);

	sq.waitForSongNotifier(5);

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(6);

	if (!skipFlag() && !shouldQuit())
		_screen->crossFadeRegion(0, 0, 8, 8, 304, 128, 2, 0);
	sq.delay(18);

	sq.printText(16, 15);           // My friends, our work is done
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(19, 36);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);
	sq.fadeText();

	sq.printText(17, 15);           // Thank you
	sq.runSequence(19);
	sq.runSequence(20, 36);
	sq.fadeText();

	sq.printText(18, 15);           // You have earned my deepest respect
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);
	sq.runSequence(20);
	sq.runSequence(19);
	sq.runSequence(19);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);
	sq.delay(36);
	sq.fadeText();

	sq.printText(19, 15);           // We will remember you always
	sq.runSequence(19);
	sq.runSequence(19, 18);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);
	sq.runSequence(20, 18);
	sq.fadeText();

	sq.delay(28);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);
	sq.delay(3);

	sq.loadScene(5, 2);
	if (skipFlag() || shouldQuit()) {
		_screen->copyRegion(0, 0, 8, 8, 304, 128, 2, 0, Screen::CR_NO_P_CHECK);
	} else {
		_sound->playTrack(6);
		_screen->crossFadeRegion(0, 0, 8, 8, 304, 128, 2, 0);
	}

	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);
	sq.delay(5);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);
	sq.delay(11);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);
	sq.delay(7);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(11);
	sq.delay(12);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(12);

	removeInputTop();
	resetSkipFlag(true);

	sq.loadScene(10, 2);
	sq.loadScene(9, 2);
	snd_stopSound();
	sq.delay(3);

	_sound->loadSoundFile("FINALE2");

	sq.delay(18);
	if (!skipFlag() && !shouldQuit())
		_sound->playTrack(1);

	seq_playCredits(&sq, _creditsData, 18, 2, 6, 2);

	sq.delay(90);

	resetSkipFlag(true);

	sq.setPalette(11);
	sq.fadePalette(9, 10);

	_screen->clearCurPage();
	sq.loadScene(11, 2);

	static const uint8 finPortraitPos[] = { 0x50, 0x50, 0xD0, 0x50, 0x50, 0x90, 0xD0, 0x90, 0x90, 0x50, 0x90, 0x90 };

	for (int i = 0; i < 6; i++) {
		if (!testCharacter(i, 1))
			continue;
		if (i > 3)
			_screen->drawShape(2, sq._shapes[6 + i], finPortraitPos[i << 1] - 16, finPortraitPos[(i << 1) + 1] - 16, 0);
		_screen->drawShape(2, _characters[i].faceShape, finPortraitPos[i << 1], finPortraitPos[(i << 1) + 1], 0);
	}

	_screen->copyRegion(0, 0, 0, 0, 320, 200, 2, 0, Screen::CR_NO_P_CHECK);

	sq.setPalette(9);
	sq.fadePalette(0, 18);

	while (!skipFlag() && !shouldQuit())
		delay(_tickLength);

	snd_stopSound();
	sq.fadePalette(9, 10);
}

void DarkMoonEngine::seq_playCredits(DarkmoonSequenceHelper *sq, const uint8 *data, int sd, int backupPage, int tempPage, int speed) {
	if (!data)
		return;

	_screen->setScreenDim(sd);
	const ScreenDim *dm = _screen->_curDim;

	_screen->copyRegion(dm->sx << 3, dm->sy, dm->sx << 3, dm->sy, dm->w << 3, dm->h, 0, backupPage, Screen::CR_NO_P_CHECK);

	struct CreditsDataItem {
		int16 x;
		int16 y;
		const void *data;
		char *str;
		uint8 crlf;
		uint8 size;
		uint8 dataType;
	} items[36];
	memset(items, 0, sizeof(items));

	const char *pos = (const char *)data;
	uint32 end = _system->getMillis();
	uint32 cur = 0;
	int i = 0;

	do {
		for (bool loop = true; loop;) {
			sq->processDelayedPaletteFade();
			cur = _system->getMillis();
			if (end <= cur)
				break;
			delay(MIN<uint32>(_tickLength, end - cur));
		}

		end = _system->getMillis() + speed * _tickLength;

		for (; i < 35 && *pos; i++) {
			int16 nextY = i ? items[i].y + items[i].size + (items[i].size >> 2) : dm->h;

			const char *posOld = pos;
			pos = strchr(pos, 0x0d);
			if (!pos)
				pos = strchr(posOld, 0x00);

			items[i + 1].crlf = *pos++;

			if (*posOld == 2) {
				const uint8 *shp = sq->_shapes[(*++posOld) - 1];
				items[i + 1].data = shp;
				items[i + 1].size = shp[1];
				items[i + 1].x = (dm->w - shp[2]) << 2 ;
				items[i + 1].dataType = 1;
				delete[] items[i + 1].str;
				items[i + 1].str = 0;

			} else {
				if (*posOld == 1) {
					posOld++;
					items[i + 1].size = 6;
				} else {
					items[i + 1].size = _screen->getFontWidth();
				}

				items[i + 1].dataType = 0;

				int l = pos - posOld;
				if (items[i + 1].crlf != 0x0d)
					l++;

				delete[] items[i + 1].str;
				items[i + 1].str = new char[l];
				memcpy(items[i + 1].str, posOld, l);
				items[i + 1].str[l - 1] = 0;
				items[i + 1].data = 0;
				items[i + 1].x = (((dm->w << 3) - (strlen(items[i + 1].str) * items[i + 1].size)) >> 1) + 1;
			}

			items[i + 1].y = nextY;
		}

		_screen->copyRegion(dm->sx << 3, dm->sy, dm->sx << 3, dm->sy, dm->w << 3, dm->h, backupPage, tempPage, Screen::CR_NO_P_CHECK);

		for (int h = 0; h < i; h++) {
			if (items[h + 1].y < dm->h) {
				if (items[h + 1].dataType == 1) {
					_screen->drawShape(tempPage, (const uint8 *)items[h + 1].data, items[h + 1].x, items[h + 1].y, sd);
				} else {
					_screen->setCurPage(tempPage);

					if (items[h + 1].size == 6)
						_screen->setFont(Screen::FID_6_FNT);

					_screen->printText(items[h + 1].str, (dm->sx << 3) + items[h + 1].x - 1, dm->sy + items[h + 1].y + 1, 12, 0);
					_screen->printText(items[h + 1].str, (dm->sx << 3) + items[h + 1].x, dm->sy + items[h + 1].y, 240, 0);

					if (items[h + 1].size == 6)
						_screen->setFont(Screen::FID_8_FNT);

					_screen->setCurPage(0);
				}
			}

			items[h + 1].y -= 2;
		}

		_screen->copyRegion(dm->sx << 3, dm->sy, dm->sx << 3, dm->sy, dm->w << 3, dm->h, tempPage, 0, Screen::CR_NO_P_CHECK);
		_screen->updateScreen();

		if (-items[1].size > items[1].y) {
			delete[] items[1].str;
			--i;
			for (int t = 1; t <= i; t++)
				memcpy(&items[t], &items[t + 1], sizeof(CreditsDataItem));
			items[i + 1].str = 0;
		}

		if (i < 35 && ((items[i].y + items[i].size) < (dm->sy + dm->h))) {
			resetSkipFlag(true);
			break;
		}

		sq->processDelayedPaletteFade();
	} while (!skipFlag() && i && !shouldQuit());

	for (i = 0; i < 35; i++)
		delete[] items[i].str;
}

DarkmoonSequenceHelper::DarkmoonSequenceHelper(OSystem *system, DarkMoonEngine *vm, Screen_EoB *screen, Mode mode, const char *const *strings, const char *const *cpsFiles, const char *const *palFiles, const EoBShapeDef **shapeDefList, const EoBSequenceStep **seqList) :
	_system(system), _vm(vm), _screen(screen), _mode(mode), _strings(strings), _cpsFiles(cpsFiles), _palFiles(palFiles), _shapeDefs(shapeDefList), _seqData(seqList) {

	for (int i = 0; _palFiles[i]; i++) {
		if (i < 4)
			_palettes[i] = &_screen->getPalette(i);
		else
			_palettes[i] = new Palette(256);
		_screen->loadPalette(_palFiles[i], *_palettes[i]);
	}

	_palettes[9] = new Palette(256);
	_palettes[9]->fill(0, 256, 0);
	_palettes[10] = new Palette(256);
	_palettes[10]->fill(0, 256, 63);
	_palettes[11] = new Palette(256);
	_palettes[11]->fill(0, 256, 0);

	_shapes = new const uint8*[30];
	memset(_shapes, 0, 30 * sizeof(uint8 *));

	_fadePalTimer = 0;
	_fadePalRate = 0;

	_screen->setScreenPalette(*_palettes[0]);
	_screen->setFont(Screen::FID_8_FNT);
	_screen->hideMouse();

	_vm->delay(150);
	_vm->_eventList.clear();
	_vm->_allowSkip = true;
}

DarkmoonSequenceHelper::~DarkmoonSequenceHelper() {
	for (int i = 4; _palFiles[i]; i++)
		delete _palettes[i];
	delete _palettes[9];
	delete _palettes[10];
	delete _palettes[11];

	for (int i = 0; i < 30; i++)
		delete[] _shapes[i];
	delete[] _shapes;

	_screen->clearCurPage();
	_screen->showMouse();
	_screen->updateScreen();

	_system->delayMillis(150);
	_vm->resetSkipFlag(true);
	_vm->_allowSkip = false;
}

void DarkmoonSequenceHelper::loadScene(int index, int pageNum) {
	char file[13];
	strcpy(file, _cpsFiles[index]);

	Common::SeekableReadStream *s = _vm->resource()->createReadStream(file);
	if (s && file[0] != 'X') {
		delete s;
		_screen->loadBitmap(_cpsFiles[index], pageNum | 1, pageNum | 1, _palettes[0]);
	} else {
		if (!s) {
			file[0] = 'X';
			s = _vm->resource()->createReadStream(file);
		}

		if (!s)
			error("DarkmoonSequenceHelper::loadScene(): CPS file loading failure in scene %d", index);

		if (_mode == kFinale)
			s->read(_palettes[0]->getData(), 768);
		else
			s->seek(768);
		_screen->loadFileDataToPage(s, 3, 64000);
		delete s;
	}

	int cp = _screen->setCurPage(pageNum);

	if (_shapeDefs[index]) {
		for (const EoBShapeDef *df = _shapeDefs[index]; df->w; df++) {
			uint16 shapeIndex = (df->index < 0) ? df->index * -1 : df->index;
			if (_shapes[shapeIndex])
				delete[] _shapes[shapeIndex];
			_shapes[shapeIndex] = _screen->encodeShape(df->x, df->y, df->w, df->h, (df->index >> 8) != 0);
		}
	}

	_screen->setCurPage(cp);
	_screen->copyPage(pageNum | 1, pageNum);

	if ((pageNum == 0 || pageNum == 1) && !_vm->skipFlag() && !_vm->shouldQuit())
		_screen->updateScreen();
}

void DarkmoonSequenceHelper::runSequence(int index, int del) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	uint32 end = 0;

	for (const EoBSequenceStep *s = _seqData[index]; s->command != 0xff && !_vm->skipFlag() && !_vm->shouldQuit(); s++) {
		int palIndex = _mode == kFinale ? (s->pal + 1) : s->pal;
		int x = s->x1;
		int y = s->y1;
		int x2 = 0;
		uint16 shapeW = 0;
		uint16 shapeH = 0;

		switch (s->command) {
		case 0:
			// flash palette
			if (s->pal)
				setPaletteWithoutTextColor(palIndex);
			delay(s->delay);
			if (_mode == kIntro && s->pal)
				setPaletteWithoutTextColor(0);
			break;

		case 1:
			// draw shape, then restore background
			shapeW = _shapes[s->obj][2];
			shapeH = _shapes[s->obj][3];

			if (_mode == kFinale) {
				_screen->setScreenDim(18);
				x -= (_screen->_curDim->sx << 3);
				y -= _screen->_curDim->sy;
				if (x < 0)
					shapeW -= ((-x >> 3) + 1);
				else
					x2 = x;
			}

			_screen->drawShape(0, _shapes[s->obj], x, y, _mode == kIntro ? 0 : 18);

			if (s->pal)
				setPaletteWithoutTextColor(palIndex);
			else
				_screen->updateScreen();

			delay(s->delay);

			if (_mode == kIntro) {
				if (s->pal)
					setPaletteWithoutTextColor(0);
				_screen->copyRegion(x - 8, y - 8, x, y, (shapeW + 1) << 3, shapeH, 2, 0, Screen::CR_NO_P_CHECK);
			} else {
				_screen->copyRegion(x2, y, x2 + (_screen->_curDim->sx << 3), y + _screen->_curDim->sy, (shapeW + 1) << 3, shapeH, 2, 0, Screen::CR_NO_P_CHECK);
			}

			_screen->updateScreen();
			break;

		case 2:
			// draw shape
			_screen->drawShape(_screen->_curPage, _shapes[s->obj], x, y, 0);

			if (s->pal)
				setPaletteWithoutTextColor(palIndex);
			else if (!_screen->_curPage)
				_screen->updateScreen();

			delay(s->delay);

			if (_mode == kIntro && s->pal)
				setPaletteWithoutTextColor(0);
			break;

		case 3:
		case 4:
			// fade shape in or out or restore background
			if (_mode == kFinale)
				break;

			_screen->setShapeFadeMode(0, true);
			_screen->setShapeFadeMode(1, true);

			end = _system->getMillis() + s->delay * _vm->tickLength();

			if (palIndex) {
				_screen->setFadeTableIndex(palIndex - 1);

				_screen->copyRegion(s->x1 - 8, s->y1 - 8, 0, 0, (_shapes[s->obj][2] + 1) << 3, _shapes[s->obj][3], 2, 4, Screen::CR_NO_P_CHECK);
				_screen->drawShape(4, _shapes[s->obj], s->x1 & 7, 0, 0);
				_screen->copyRegion(0, 0, s->x1, s->y1, (_shapes[s->obj][2] + 1) << 3, _shapes[s->obj][3], 4, 0, Screen::CR_NO_P_CHECK);
			} else {
				_screen->copyRegion(s->x1 - 8, s->y1 - 8, s->x1, s->y1, (_shapes[s->obj][2] + 1) << 3, _shapes[s->obj][3], 2, 0, Screen::CR_NO_P_CHECK);
			}
			_screen->updateScreen();

			_vm->delayUntil(end);
			_screen->setShapeFadeMode(0, false);
			_screen->setShapeFadeMode(1, false);
			break;

		case 5:
			// copy region
			if (_mode == kFinale && s->pal)
				setPaletteWithoutTextColor(palIndex);

			_screen->copyRegion(s->x2 << 3, s->y2, s->x1, s->y1, s->w << 3, s->h, (s->obj && _mode == kFinale) ? 6 : 2, 0, Screen::CR_NO_P_CHECK);
			_screen->updateScreen();
			delay(s->delay);
			break;

		case 6:
			// play sound effect
			if (s->obj != 0xff)
				_vm->sound()->playSoundEffect(s->obj);
			break;

		default:
			error("DarkmoonSequenceHelper::runSequence(): Unknown animation opcode encountered.");
			break;
		}
	}

	if (del > 0)
		delay(del);
}

void DarkmoonSequenceHelper::printText(int index, int color) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	_screen->setClearScreenDim(17);
	_palettes[0]->copy(*_palettes[0], color, 1, 255);
	setPalette(0);

	char *temp = new char[strlen(_strings[index]) + 1];
	char *str = temp;
	strcpy(str, _strings[index]);

	const ScreenDim *dm = _screen->_curDim;

	for (int yOffs = 0; *str; yOffs += 9) {
		char *cr = strchr(str, 13);

		if (cr)
			*cr = 0;

		uint32 len = strlen(str);
		_screen->printText(str, (dm->sx + ((dm->w - len) >> 1)) << 3, dm->sy + yOffs, 255, dm->unkA);

		if (cr) {
			*cr = 13;
			str = cr + 1;
		} else {
			str += len;
		}
	}

	delete[] temp;
	_screen->updateScreen();
}

void DarkmoonSequenceHelper::fadeText() {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	_screen->fadeTextColor(_palettes[0], 255, 8);
	_screen->clearCurDim();
}

void DarkmoonSequenceHelper::update(int srcPage) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	_screen->copyRegion(0, 0, 8, 8, 304, 128, srcPage, 0, Screen::CR_NO_P_CHECK);
	setPaletteWithoutTextColor(0);
}

void DarkmoonSequenceHelper::setPaletteWithoutTextColor(int index) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	if (!memcmp(_palettes[11]->getData(), _palettes[index]->getData(), 765))
		return;

	_palettes[11]->copy(*_palettes[index], 0, 255);
	_palettes[11]->copy(*_palettes[0], 255, 1, 255);
	setPalette(11);

	_screen->updateScreen();
}

void DarkmoonSequenceHelper::setPalette(int index) {
	_screen->setScreenPalette(*_palettes[index]);
}

void DarkmoonSequenceHelper::fadePalette(int index, int del) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	_screen->fadePalette(*_palettes[index], del * _vm->tickLength());
}

void DarkmoonSequenceHelper::copyPalette(int srcIndex, int destIndex) {
	_palettes[destIndex]->copy(*_palettes[srcIndex]);
}

void DarkmoonSequenceHelper::initDelayedPaletteFade(int palIndex, int rate) {
	_palettes[11]->copy(*_palettes[0]);

	_fadePalIndex = palIndex;
	_fadePalRate = rate;
	_fadePalTimer = _system->getMillis() + 2 * _vm->_tickLength;
}

bool DarkmoonSequenceHelper::processDelayedPaletteFade() {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return true;

	if (!_fadePalRate || (_system->getMillis() <= _fadePalTimer))
		return false;

	if (_screen->delayedFadePalStep(_palettes[_fadePalIndex], _palettes[0], _fadePalRate)) {
		setPaletteWithoutTextColor(0);
		_fadePalTimer = _system->getMillis() + 3 * _vm->_tickLength;
	} else {
		_fadePalRate = 0;
	}

	return false;
}

void DarkmoonSequenceHelper::delay(uint32 ticks) {
	if (_vm->skipFlag() || _vm->shouldQuit())
		return;

	uint32 end = _system->getMillis() + ticks * _vm->_tickLength;

	if (_mode == kFinale) {
		do {
			if (processDelayedPaletteFade())
				break;
			_vm->updateInput();
		} while (end > _system->getMillis());
		processDelayedPaletteFade();

	} else {
		_vm->delayUntil(end);
	}
}

void DarkmoonSequenceHelper::waitForSongNotifier(int index, bool introUpdateAnim) {
	int seq = 0;
	while (_vm->sound()->checkTrigger() < index && !(_vm->skipFlag() || _vm->shouldQuit())) {
		if (introUpdateAnim) {
			runSequence(30 | seq);
			seq ^= 1;
		}

		if (_mode == kFinale)
			processDelayedPaletteFade();

		_vm->updateInput();
	}
}

void DarkMoonEngine::seq_nightmare() {
	Screen::FontId of = _screen->setFont(Screen::FID_6_FNT);
	_screen->copyRegion(0, 0, 0, 120, 176, 24, 12, 2, Screen::CR_NO_P_CHECK);

	initDialogueSequence();
	gui_drawDialogueBox();

	_txt->printDialogueText(99, 0);
	snd_playSoundEffect(54);

	static const uint8 seqX[] = { 0, 20, 0, 20 };
	static const uint8 seqY[] = { 0, 0, 96, 96 };
	static const uint8 seqDelay[] = { 12, 7, 7, 12 };

	for (const int8 *i = _dreamSteps; *i != -1; ++i) {
		drawSequenceBitmap("DREAM", 0, seqX[*i], seqY[*i], 0);
		delay(seqDelay[*i] * _tickLength);
	}

	_txt->printDialogueText(20, _okStrings[0]);

	restoreAfterDialogueSequence();

	_screen->setFont(of);
}

void DarkMoonEngine::seq_kheldran() {
	Screen::FontId of = _screen->setFont(Screen::FID_6_FNT);

	initDialogueSequence();
	gui_drawDialogueBox();

	static const char file[] = "KHELDRAN";
	_txt->printDialogueText(_kheldranStrings[0]);
	drawSequenceBitmap(file, 0, 0, 0, 0);
	_txt->printDialogueText(20, _moreStrings[0]);
	snd_playSoundEffect(56);
	drawSequenceBitmap(file, 0, 20, 0, 0);
	delay(10 * _tickLength);
	drawSequenceBitmap(file, 0, 0, 96, 0);
	delay(10 * _tickLength);
	drawSequenceBitmap(file, 0, 20, 96, 0);
	delay(7 * _tickLength);
	_txt->printDialogueText(76, _okStrings[0]);

	restoreAfterDialogueSequence();

	_screen->setFont(of);
}

void DarkMoonEngine::seq_dranDragonTransformation() {
	Screen::FontId of = _screen->setFont(Screen::FID_6_FNT);

	initDialogueSequence();
	gui_drawDialogueBox();

	static const char file[] = "DRANX";
	drawSequenceBitmap(file, 0, 0, 0, 0);
	_txt->printDialogueText(120, _moreStrings[0]);
	snd_playSoundEffect(56);
	drawSequenceBitmap(file, 0, 20, 0, 0);
	delay(7 * _tickLength);
	drawSequenceBitmap(file, 0, 0, 96, 0);
	delay(7 * _tickLength);
	drawSequenceBitmap(file, 0, 20, 96, 0);
	delay(18 * _tickLength);

	restoreAfterDialogueSequence();

	_screen->setFont(of);
}

} // End of namespace Kyra

#endif // ENABLE_EOB
