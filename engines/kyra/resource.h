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

#ifndef KYRA_RESOURCE_H
#define KYRA_RESOURCE_H


#include "common/scummsys.h"
#include "common/str.h"
#include "common/file.h"
#include "common/list.h"
#include "common/hash-str.h"
#include "common/hashmap.h"
#include "common/stream.h"
#include "common/ptr.h"
#include "common/archive.h"

#include "kyra/kyra_v1.h"
#include "kyra/darkmoon.h"
#include "kyra/lol.h"
#include "kyra/kyra_hof.h"

namespace Kyra {

class Resource;

class ResArchiveLoader;

class Resource {
public:
	Resource(KyraEngine_v1 *vm);
	~Resource();

	bool reset();

	bool loadPakFile(Common::String filename);
	bool loadPakFile(Common::String name, Common::ArchiveMemberPtr file);

	void unloadPakFile(Common::String filename, bool remFromCache = false);

	bool isInPakList(Common::String filename);

	bool isInCacheList(Common::String name);

	bool loadFileList(const Common::String &filedata);
	bool loadFileList(const char * const *filelist, uint32 numFiles);

	// This unloads *all* pakfiles, even kyra.dat and protected ones.
	// It does not remove files from cache though!
	void unloadAllPakFiles();

	void listFiles(const Common::String &pattern, Common::ArchiveMemberList &list);

	bool exists(const char *file, bool errorOutOnFail=false);
	uint32 getFileSize(const char *file);
	uint8 *fileData(const char *file, uint32 *size);
	Common::SeekableReadStream *createReadStream(const Common::String &file);

	bool loadFileToBuf(const char *file, void *buf, uint32 maxSize);
protected:
	typedef Common::HashMap<Common::String, Common::Archive *, Common::CaseSensitiveString_Hash, Common::CaseSensitiveString_EqualTo> ArchiveMap;
	ArchiveMap _archiveCache;

	Common::SearchSet _files;
	Common::SearchSet _archiveFiles;
	Common::SearchSet _protectedFiles;

	Common::Archive *loadArchive(const Common::String &name, Common::ArchiveMemberPtr member);
	Common::Archive *loadInstallerArchive(const Common::String &file, const Common::String &ext, const uint8 offset);

	bool loadProtectedFiles(const char * const * list);

	void initializeLoaders();

	typedef Common::List<Common::SharedPtr<ResArchiveLoader> > LoaderList;
	LoaderList _loaders;

	KyraEngine_v1 *_vm;
};

enum KyraResources {
	kLoadAll = -1,

	// This list has to match orderwise (and thus value wise) the static data list of "devtools/create_kyradat/create_kyradat.h"!
	k1ForestSeq = 1,
	k1KallakWritingSeq,
	k1KyrandiaLogoSeq,
	k1KallakMalcolmSeq,
	k1MalcolmTreeSeq,
	k1WestwoodLogoSeq,

	k1Demo1Seq,
	k1Demo2Seq,
	k1Demo3Seq,
	k1Demo4Seq,

	k1AmuleteAnimSeq,

	k1OutroReunionSeq,

	k1IntroCPSStrings,
	k1IntroCOLStrings,
	k1IntroWSAStrings,
	k1IntroStrings,

	k1OutroHomeString,

	k1RoomFilenames,
	k1RoomList,

	k1CharacterImageFilenames,

	k1ItemNames,
	k1TakenStrings,
	k1PlacedStrings,
	k1DroppedStrings,
	k1NoDropStrings,

	k1PutDownString,
	k1WaitAmuletString,
	k1BlackJewelString,
	k1PoisonGoneString,
	k1HealingTipString,
	k1WispJewelStrings,
	k1MagicJewelStrings,

	k1ThePoisonStrings,
	k1FluteStrings,

	k1FlaskFullString,
	k1FullFlaskString,

	k1VeryCleverString,
	k1NewGameString,

	k1DefaultShapes,
	k1Healing1Shapes,
	k1Healing2Shapes,
	k1PoisonDeathShapes,
	k1FluteShapes,
	k1Winter1Shapes,
	k1Winter2Shapes,
	k1Winter3Shapes,
	k1DrinkShapes,
	k1WispShapes,
	k1MagicAnimShapes,
	k1BranStoneShapes,

	k1SpecialPalette1,
	k1SpecialPalette2,
	k1SpecialPalette3,
	k1SpecialPalette4,
	k1SpecialPalette5,
	k1SpecialPalette6,
	k1SpecialPalette7,
	k1SpecialPalette8,
	k1SpecialPalette9,
	k1SpecialPalette10,
	k1SpecialPalette11,
	k1SpecialPalette12,
	k1SpecialPalette13,
	k1SpecialPalette14,
	k1SpecialPalette15,
	k1SpecialPalette16,
	k1SpecialPalette17,
	k1SpecialPalette18,
	k1SpecialPalette19,
	k1SpecialPalette20,
	k1SpecialPalette21,
	k1SpecialPalette22,
	k1SpecialPalette23,
	k1SpecialPalette24,
	k1SpecialPalette25,
	k1SpecialPalette26,
	k1SpecialPalette27,
	k1SpecialPalette28,
	k1SpecialPalette29,
	k1SpecialPalette30,
	k1SpecialPalette31,
	k1SpecialPalette32,
	k1SpecialPalette33,

	k1GUIStrings,
	k1ConfigStrings,

	k1AudioTracks,
	k1AudioTracks2,
	k1AudioTracksIntro,

	k1CreditsStrings,

	k1TownsMusicFadeTable,
	k1TownsSFXwdTable,
	k1TownsSFXbtTable,
	k1TownsCDATable,

	k1PC98StoryStrings,
	k1PC98IntroSfx,

	k1AmigaIntroSFXTable,
	k1AmigaGameSFXTable,

	k2SeqplayPakFiles,
	k2SeqplayCredits,
	k2SeqplayCreditsSpecial,
	k2SeqplayStrings,
	k2SeqplaySfxFiles,
	k2SeqplayTlkFiles,
	k2SeqplaySeqData,
	k2SeqplayIntroTracks,
	k2SeqplayFinaleTracks,
	k2SeqplayIntroCDA,
	k2SeqplayFinaleCDA,
	k2SeqplayShapeAnimData,

	k2IngamePakFiles,
	k2IngameSfxFiles,
	k2IngameSfxIndex,
	k2IngameTracks,
	k2IngameCDA,
	k2IngameTalkObjIndex,
	k2IngameTimJpStrings,
	k2IngameShapeAnimData,
	k2IngameTlkDemoStrings,

	k3MainMenuStrings,
	k3MusicFiles,
	k3ScoreTable,
	k3SfxFiles,
	k3SfxMap,
	k3ItemAnimData,
	k3ItemMagicTable,
	k3ItemStringMap,

#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	kRpgCommonMoreStrings,
	kRpgCommonDscShapeIndex,
	kRpgCommonDscX,
	kRpgCommonDscTileIndex,
	kRpgCommonDscUnk2,
	kRpgCommonDscDoorShapeIndex,
	kRpgCommonDscDimData1,
	kRpgCommonDscDimData2,
	kRpgCommonDscBlockMap,
	kRpgCommonDscDimMap,
	kRpgCommonDscDoorY2,
	kRpgCommonDscBlockIndex,

	kEoBBaseChargenStrings1,
	kEoBBaseChargenStrings2,
	kEoBBaseChargenStartLevels,
	kEoBBaseChargenStatStrings,
	kEoBBaseChargenRaceSexStrings,
	kEoBBaseChargenClassStrings,
	kEoBBaseChargenAlignmentStrings,
	kEoBBaseChargenEnterGameStrings,
	kEoBBaseChargenClassMinStats,
	kEoBBaseChargenRaceMinStats,
	kEoBBaseChargenRaceMaxStats,

	kEoBBaseSaveThrowTable1,
	kEoBBaseSaveThrowTable2,
	kEoBBaseSaveThrowTable3,
	kEoBBaseSaveThrowTable4,
	kEoBBaseSaveThrwLvlIndex,
	kEoBBaseSaveThrwModDiv,
	kEoBBaseSaveThrwModExt,

	kEoBBasePryDoorStrings,
	kEoBBaseWarningStrings,

	kEoBBaseItemSuffixStringsRings,
	kEoBBaseItemSuffixStringsPotions,
	kEoBBaseItemSuffixStringsWands,

	kEoBBaseRipItemStrings,
	kEoBBaseCursedString,
	kEoBBaseEnchantedString,
	kEoBBaseMagicObjectStrings,
	kEoBBaseMagicObjectString5,
	kEoBBasePatternSuffix,
	kEoBBasePatternGrFix1,
	kEoBBasePatternGrFix2,
	kEoBBaseValidateArmorString,
	kEoBBaseValidateCursedString,
	kEoBBaseValidateNoDropString,
	kEoBBasePotionStrings,
	kEoBBaseWandStrings,
	kEoBBaseItemMisuseStrings,

	kEoBBaseTakenStrings,
	kEoBBasePotionEffectStrings,

	kEoBBaseYesNoStrings,
	kEoBBaseNpcMaxStrings,
	kEoBBaseOkStrings,
	kEoBBaseNpcJoinStrings,
	kEoBBaseCancelStrings,
	kEoBBaseAbortStrings,

	kEoBBaseMenuStringsMain,
	kEoBBaseMenuStringsSaveLoad,
	kEoBBaseMenuStringsOnOff,
	kEoBBaseMenuStringsSpells,
	kEoBBaseMenuStringsRest,
	kEoBBaseMenuStringsDrop,
	kEoBBaseMenuStringsExit,
	kEoBBaseMenuStringsStarve,
	kEoBBaseMenuStringsScribe,
	kEoBBaseMenuStringsDrop2,
	kEoBBaseMenuStringsHead,
	kEoBBaseMenuStringsPoison,
	kEoBBaseMenuStringsMgc,
	kEoBBaseMenuStringsPrefs,
	kEoBBaseMenuStringsRest2,
	kEoBBaseMenuStringsRest3,
	kEoBBaseMenuStringsRest4,
	kEoBBaseMenuStringsDefeat,
	kEoBBaseMenuStringsTransfer,
	kEoBBaseMenuStringsSpec,
	kEoBBaseMenuStringsSpellNo,
	kEoBBaseMenuYesNoStrings,

	kEoBBaseSpellLevelsMage,
	kEoBBaseSpellLevelsCleric,
	kEoBBaseNumSpellsCleric,
	kEoBBaseNumSpellsWisAdj,
	kEoBBaseNumSpellsPal,
	kEoBBaseNumSpellsMage,

	kEoBBaseCharGuiStringsHp,
	kEoBBaseCharGuiStringsWp1,
	kEoBBaseCharGuiStringsWp2,
	kEoBBaseCharGuiStringsWr,
	kEoBBaseCharGuiStringsSt1,
	kEoBBaseCharGuiStringsSt2,
	kEoBBaseCharGuiStringsIn,

	kEoBBaseCharStatusStrings7,
	kEoBBaseCharStatusStrings81,
	kEoBBaseCharStatusStrings82,
	kEoBBaseCharStatusStrings9,
	kEoBBaseCharStatusStrings12,
	kEoBBaseCharStatusStrings131,
	kEoBBaseCharStatusStrings132,

	kEoBBaseLevelGainStrings,
	kEoBBaseExperienceTable0,
	kEoBBaseExperienceTable1,
	kEoBBaseExperienceTable2,
	kEoBBaseExperienceTable3,
	kEoBBaseExperienceTable4,

	kEoBBaseClassModifierFlags,

	kEoBBaseMonsterStepTable01,
	kEoBBaseMonsterStepTable02,
	kEoBBaseMonsterStepTable1,
	kEoBBaseMonsterStepTable2,
	kEoBBaseMonsterStepTable3,
	kEoBBaseMonsterCloseAttPosTable1,
	kEoBBaseMonsterCloseAttPosTable21,
	kEoBBaseMonsterCloseAttPosTable22,
	kEoBBaseMonsterCloseAttUnkTable,
	kEoBBaseMonsterCloseAttChkTable1,
	kEoBBaseMonsterCloseAttChkTable2,
	kEoBBaseMonsterCloseAttDstTable1,
	kEoBBaseMonsterCloseAttDstTable2,

	kEoBBaseMonsterProximityTable,
	kEoBBaseFindBlockMonstersTable,
	kEoBBaseMonsterDirChangeTable,
	kEoBBaseMonsterDistAttStrings,

	kEoBBaseEncodeMonsterDefs,
	kEoBBaseNpcPresets,

	kEoBBaseWllFlagPreset,
	kEoBBaseDscShapeCoords,

	kEoBBaseDscDoorScaleOffs,
	kEoBBaseDscDoorScaleMult1,
	kEoBBaseDscDoorScaleMult2,
	kEoBBaseDscDoorScaleMult3,
	kEoBBaseDscDoorScaleMult4,
	kEoBBaseDscDoorScaleMult5,
	kEoBBaseDscDoorScaleMult6,
	kEoBBaseDscDoorType5Offs,
	kEoBBaseDscDoorXE,
	kEoBBaseDscDoorY1,
	kEoBBaseDscDoorY3,
	kEoBBaseDscDoorY4,
	kEoBBaseDscDoorY5,
	kEoBBaseDscDoorY6,
	kEoBBaseDscDoorY7,
	kEoBBaseDscDoorCoordsExt,

	kEoBBaseDscItemPosIndex,
	kEoBBaseDscItemShpX,
	kEoBBaseDscItemScaleIndex,
	kEoBBaseDscItemTileIndex,
	kEoBBaseDscItemShapeMap,

	kEoBBaseDscMonsterFrmOffsTbl1,
	kEoBBaseDscMonsterFrmOffsTbl2,

	kEoBBaseInvSlotX,
	kEoBBaseInvSlotY,
	kEoBBaseSlotValidationFlags,

	kEoBBaseProjectileWeaponTypes,
	kEoBBaseWandTypes,

	kEoBBaseDrawObjPosIndex,
	kEoBBaseFlightObjFlipIndex,
	kEoBBaseFlightObjShpMap,
	kEoBBaseFlightObjSclIndex,

	kEoBBaseDscTelptrShpCoords,

	kEoBBasePortalSeqData,
	kEoBBaseManDef,
	kEoBBaseManWord,
	kEoBBaseManPrompt,

	kEoBBaseBookNumbers,
	kEoBBaseMageSpellsList,
	kEoBBaseClericSpellsList,
	kEoBBaseSpellNames,
	kEoBBaseMagicStrings1,
	kEoBBaseMagicStrings2,
	kEoBBaseMagicStrings3,
	kEoBBaseMagicStrings4,
	kEoBBaseMagicStrings6,
	kEoBBaseMagicStrings7,
	kEoBBaseMagicStrings8,

	kEoBBaseExpObjectTlMode,
	kEoBBaseExpObjectTblIndex,
	kEoBBaseExpObjectShpStart,
	kEoBBaseExpObjectTbl1,
	kEoBBaseExpObjectTbl2,
	kEoBBaseExpObjectTbl3,
	kEoBBaseExpObjectY,

	kEoBBaseSparkDefSteps,
	kEoBBaseSparkDefSubSteps,
	kEoBBaseSparkDefShift,
	kEoBBaseSparkDefAdd,
	kEoBBaseSparkDefX,
	kEoBBaseSparkDefY,
	kEoBBaseSparkOfFlags1,
	kEoBBaseSparkOfFlags2,
	kEoBBaseSparkOfShift,
	kEoBBaseSparkOfX,
	kEoBBaseSparkOfY,

	kEoBBaseSpellProperties,
	kEoBBaseMagicFlightProps,
	kEoBBaseTurnUndeadEffect,
	kEoBBaseBurningHandsDest,
	kEoBBaseConeOfColdDest1,
	kEoBBaseConeOfColdDest2,
	kEoBBaseConeOfColdDest3,
	kEoBBaseConeOfColdDest4,
	kEoBBaseConeOfColdGfxTbl,

	kEoB1MainMenuStrings,
	kEoB1BonusStrings,

	kEoB1IntroFilesOpening,
	kEoB1IntroFilesTower,
	kEoB1IntroFilesOrb,
	kEoB1IntroFilesWdEntry,
	kEoB1IntroFilesKing,
	kEoB1IntroFilesHands,
	kEoB1IntroFilesWdExit,
	kEoB1IntroFilesTunnel,
	kEoB1IntroOpeningFrmDelay,
	kEoB1IntroWdEncodeX,
	kEoB1IntroWdEncodeY,
	kEoB1IntroWdEncodeWH,
	kEoB1IntroWdDsX,
	kEoB1IntroWdDsY,
	kEoB1IntroTvlX1,
	kEoB1IntroTvlY1,
	kEoB1IntroTvlX2,
	kEoB1IntroTvlY2,
	kEoB1IntroTvlW,
	kEoB1IntroTvlH,

	kEoB1DoorShapeDefs,
	kEoB1DoorSwitchShapeDefs,
	kEoB1DoorSwitchCoords,
	kEoB1MonsterProperties,

	kEoB1EnemyMageSpellList,
	kEoB1EnemyMageSfx,
	kEoB1BeholderSpellList,
	kEoB1BeholderSfx,

	kEoB1TurnUndeadString,

	kEoB1NpcShpData,
	kEoB1NpcSubShpIndex1,
	kEoB1NpcSubShpIndex2,
	kEoB1NpcSubShpY,
	kEoB1Npc0Strings,
	kEoB1Npc11Strings,
	kEoB1Npc12Strings,
	kEoB1Npc21Strings,
	kEoB1Npc22Strings,
	kEoB1Npc31Strings,
	kEoB1Npc32Strings,
	kEoB1Npc4Strings,
	kEoB1Npc5Strings,
	kEoB1Npc6Strings,
	kEoB1Npc7Strings,

	kEoB2MainMenuStrings,

	kEoB2TransferPortraitFrames,
	kEoB2TransferConvertTable,
	kEoB2TransferItemTable,
	kEoB2TransferExpTable,
	kEoB2TransferStrings1,
	kEoB2TransferStrings2,
	kEoB2TransferLabels,

	kEoB2IntroStrings,
	kEoB2IntroCPSFiles,
	kEoB2IntroSeqData00,
	kEoB2IntroSeqData01,
	kEoB2IntroSeqData02,
	kEoB2IntroSeqData03,
	kEoB2IntroSeqData04,
	kEoB2IntroSeqData05,
	kEoB2IntroSeqData06,
	kEoB2IntroSeqData07,
	kEoB2IntroSeqData08,
	kEoB2IntroSeqData09,
	kEoB2IntroSeqData10,
	kEoB2IntroSeqData11,
	kEoB2IntroSeqData12,
	kEoB2IntroSeqData13,
	kEoB2IntroSeqData14,
	kEoB2IntroSeqData15,
	kEoB2IntroSeqData16,
	kEoB2IntroSeqData17,
	kEoB2IntroSeqData18,
	kEoB2IntroSeqData19,
	kEoB2IntroSeqData20,
	kEoB2IntroSeqData21,
	kEoB2IntroSeqData22,
	kEoB2IntroSeqData23,
	kEoB2IntroSeqData24,
	kEoB2IntroSeqData25,
	kEoB2IntroSeqData26,
	kEoB2IntroSeqData27,
	kEoB2IntroSeqData28,
	kEoB2IntroSeqData29,
	kEoB2IntroSeqData30,
	kEoB2IntroSeqData31,
	kEoB2IntroSeqData32,
	kEoB2IntroSeqData33,
	kEoB2IntroSeqData34,
	kEoB2IntroSeqData35,
	kEoB2IntroSeqData36,
	kEoB2IntroSeqData37,
	kEoB2IntroSeqData38,
	kEoB2IntroSeqData39,
	kEoB2IntroSeqData40,
	kEoB2IntroSeqData41,
	kEoB2IntroSeqData42,
	kEoB2IntroSeqData43,
	kEoB2IntroShapes00,
	kEoB2IntroShapes01,
	kEoB2IntroShapes04,
	kEoB2IntroShapes07,

	kEoB2FinaleStrings,
	kEoB2CreditsData,
	kEoB2FinaleCPSFiles,
	kEoB2FinaleSeqData00,
	kEoB2FinaleSeqData01,
	kEoB2FinaleSeqData02,
	kEoB2FinaleSeqData03,
	kEoB2FinaleSeqData04,
	kEoB2FinaleSeqData05,
	kEoB2FinaleSeqData06,
	kEoB2FinaleSeqData07,
	kEoB2FinaleSeqData08,
	kEoB2FinaleSeqData09,
	kEoB2FinaleSeqData10,
	kEoB2FinaleSeqData11,
	kEoB2FinaleSeqData12,
	kEoB2FinaleSeqData13,
	kEoB2FinaleSeqData14,
	kEoB2FinaleSeqData15,
	kEoB2FinaleSeqData16,
	kEoB2FinaleSeqData17,
	kEoB2FinaleSeqData18,
	kEoB2FinaleSeqData19,
	kEoB2FinaleSeqData20,
	kEoB2FinaleShapes00,
	kEoB2FinaleShapes03,
	kEoB2FinaleShapes07,
	kEoB2FinaleShapes09,
	kEoB2FinaleShapes10,

	kEoB2NpcShapeData,
	kEoB2Npc1Strings,
	kEoB2Npc2Strings,
	kEoB2MonsterDustStrings,

	kEoB2DreamSteps,
	kEoB2KheldranStrings,
	kEoB2HornStrings,
	kEoB2HornSounds,

	kEoB2WallOfForceDsX,
	kEoB2WallOfForceDsY,
	kEoB2WallOfForceNumW,
	kEoB2WallOfForceNumH,
	kEoB2WallOfForceShpId,

	kLoLIngamePakFiles,
	kLoLCharacterDefs,
	kLoLIngameSfxFiles,
	kLoLIngameSfxIndex,
	kLoLMusicTrackMap,
	kLoLIngameGMSfxIndex,
	kLoLIngameMT32SfxIndex,
	kLoLIngamePcSpkSfxIndex,
	kLoLSpellProperties,
	kLoLGameShapeMap,
	kLoLSceneItemOffs,
	kLoLCharInvIndex,
	kLoLCharInvDefs,
	kLoLCharDefsMan,
	kLoLCharDefsWoman,
	kLoLCharDefsKieran,
	kLoLCharDefsAkshel,
	kLoLExpRequirements,
	kLoLMonsterModifiers,
	kLoLMonsterShiftOffsets,
	kLoLMonsterDirFlags,
	kLoLMonsterScaleY,
	kLoLMonsterScaleX,
	kLoLMonsterScaleWH,
	kLoLFlyingObjectShp,
	kLoLInventoryDesc,

	kLoLLevelShpList,
	kLoLLevelDatList,
	kLoLCompassDefs,
	kLoLItemPrices,
	kLoLStashSetup,

	kLoLDscWalls,
	kLoLDscOvlMap,
	kLoLDscScaleWidthData,
	kLoLDscScaleHeightData,
	kLoLBaseDscY,

	kLoLDscDoorScale,
	kLoLDscDoor4,
	kLoLDscDoorX,
	kLoLDscDoorY,
	kLoLDscOvlIndex,

	kLoLScrollXTop,
	kLoLScrollYTop,
	kLoLScrollXBottom,
	kLoLScrollYBottom,

	kLoLButtonDefs,
	kLoLButtonList1,
	kLoLButtonList2,
	kLoLButtonList3,
	kLoLButtonList4,
	kLoLButtonList5,
	kLoLButtonList6,
	kLoLButtonList7,
	kLoLButtonList8,

	kLoLLegendData,
	kLoLMapCursorOvl,
	kLoLMapStringId,

	kLoLSpellbookAnim,
	kLoLSpellbookCoords,
	kLoLHealShapeFrames,
	kLoLLightningDefs,
	kLoLFireballCoords,

	kLoLCredits,

	kLoLHistory,
#endif // ENABLE_EOB || ENABLE_LOL

	kMaxResIDs
};

struct Shape;
struct Room;
struct AmigaSfxTable;

class StaticResource {
public:
	static const Common::String staticDataFilename() { return "KYRA.DAT"; }

	StaticResource(KyraEngine_v1 *vm) : _vm(vm), _resList(), _fileLoader(0), _dataTable() {}
	~StaticResource() { deinit(); }

	bool loadStaticResourceFile();

	bool init();
	void deinit();

	const char * const *loadStrings(int id, int &strings);
	const uint8 *loadRawData(int id, int &size);
	const Shape *loadShapeTable(int id, int &entries);
	const AmigaSfxTable *loadAmigaSfxTable(int id, int &entries);
	const Room *loadRoomTable(int id, int &entries);
	const HofSeqData *loadHofSequenceData(int id, int &entries);
	const ItemAnimData_v1 *loadShapeAnimData_v1(int id, int &entries);
	const ItemAnimData_v2 *loadShapeAnimData_v2(int id, int &entries);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	const uint16 *loadRawDataBe16(int id, int &entries);
	const uint32 *loadRawDataBe32(int id, int &entries);
#endif // (ENABLE_EOB || ENABLE_LOL)
#ifdef ENABLE_LOL
	const LoLCharacter *loadCharData(int id, int &entries);
	const SpellProperty *loadSpellData(int id, int &entries);
	const CompassDef *loadCompassData(int id, int &entries);
	const FlyingObjectShape *loadFlyingObjectData(int id, int &entries);
	const LoLButtonDef *loadButtonDefs(int id, int &entries);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	const EoBSequenceStep *loadEoB2SeqData(int id, int &entries);
	const EoBShapeDef *loadEoB2ShapeData(int id, int &entries);
	const EoBCharacter *loadEoBNpcData(int id, int &entries);
#endif // ENABLE_EOB

	// use '-1' to prefetch/unload all ids
	// prefetchId retruns false if only on of the resources
	// can't be loaded and it breaks then the first res
	// can't be loaded
	bool prefetchId(int id);
	void unloadId(int id);
private:
	bool tryKyraDatLoad();

	KyraEngine_v1 *_vm;

	struct FileType;

	bool checkResList(int id, int &type, const void *&ptr, int &size);
	const FileType *getFiletype(int type);
	const void *getData(int id, int requesttype, int &size);

	bool loadDummy(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadStringTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRawData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadAmigaSfxTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRoomTable(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadHofSequenceData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeAnimData_v1(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadShapeAnimData_v2(Common::SeekableReadStream &stream, void *&ptr, int &size);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	bool loadRawDataBe16(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadRawDataBe32(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // (ENABLE_LOL || ENABLE_EOB)
#ifdef ENABLE_LOL
	bool loadCharData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadSpellData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadCompassData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadFlyingObjectData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadButtonDefs(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	bool loadEoB2SeqData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadEoB2ShapeData(Common::SeekableReadStream &stream, void *&ptr, int &size);
	bool loadEoBNpcData(Common::SeekableReadStream &stream, void *&ptr, int &size);
#endif // ENABLE_EOB

	void freeDummy(void *&ptr, int &size);
	void freeRawData(void *&ptr, int &size);
	void freeStringTable(void *&ptr, int &size);
	void freeShapeTable(void *&ptr, int &size);
	void freeAmigaSfxTable(void *&ptr, int &size);
	void freeRoomTable(void *&ptr, int &size);
	void freeHofSequenceData(void *&ptr, int &size);
	void freeHofShapeAnimDataV1(void *&ptr, int &size);
	void freeHofShapeAnimDataV2(void *&ptr, int &size);
#if defined(ENABLE_EOB) || defined(ENABLE_LOL)
	void freeRawDataBe16(void *&ptr, int &size);
	void freeRawDataBe32(void *&ptr, int &size);
#endif // (ENABLE_EOB || ENABLE_LOL)
#ifdef ENABLE_LOL
	void freeCharData(void *&ptr, int &size);
	void freeSpellData(void *&ptr, int &size);
	void freeCompassData(void *&ptr, int &size);
	void freeFlyingObjectData(void *&ptr, int &size);
	void freeButtonDefs(void *&ptr, int &size);
#endif // ENABLE_LOL
#ifdef ENABLE_EOB
	void freeEoB2SeqData(void *&ptr, int &size);
	void freeEoB2ShapeData(void *&ptr, int &size);
	void freeEoBNpcData(void *&ptr, int &size);
#endif // ENABLE_EOB

	enum ResTypes {
		kStringList = 0,
		kRawData = 1,
		kRoomList = 2,
		kShapeList = 3,
		kAmigaSfxTable = 4,

		k2SeqData = 5,
		k2ShpAnimDataV1 = 6,
		k2ShpAnimDataV2 = 7,

		kLoLCharData = 8,
		kLoLSpellData = 9,
		kLoLCompassData = 10,
		kLoLFlightShpData = 11,
		kLoLButtonData = 12,
		kRawDataBe16 = 13,
		kRawDataBe32 = 14,

		kEoB2SequenceData = 15,
		kEoB2ShapeData = 16,
		kEoBNpcData = 17
	};

	struct FileType {
		int type;
		typedef bool (StaticResource::*LoadFunc)(Common::SeekableReadStream &stream, void *&ptr, int &size);
		typedef void (StaticResource::*FreeFunc)(void *&ptr, int &size);

		LoadFunc load;
		FreeFunc free;
	};

	struct ResData {
		int id;
		int type;
		int size;
		void *data;
	};

	Common::List<ResData> _resList;

	const FileType *_fileLoader;

	struct DataDescriptor {
		DataDescriptor() : filename(0), type(0) {}
		DataDescriptor(uint32 f, uint8 t) : filename(f), type(t) {}

		uint32 filename;
		uint8 type;
	};
	typedef Common::HashMap<uint16, DataDescriptor> DataMap;
	DataMap _dataTable;
};

} // End of namespace Kyra

#endif
