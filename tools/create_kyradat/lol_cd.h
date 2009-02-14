const ExtractEntry lolCDFile2[] = {
	{ lolCharacterDefs, 0x00029D60, 0x0002A1F2 },
	{ lolIngameSfxFiles, 0x0002A330, 0x0002AC22 },
	{ lolIngameSfxIndex, 0x0002AC22, 0x0002B00A },
	{ lolMusicTrackMap, 0x0002A240, 0x0002A330 },	
	{ lolGMSfxIndex, 0x0002B010, 0x0002B10A },
	{ lolMT32SfxIndex, 0x0002B110, 0x0002B20A },
	//{ lolADLSfxIndex, 0x0002B210, 0x0002B30A },
	{ lolSpellProperties, 0x0002B5D0, 0x0002B6E8 },
	{ lolGameShapeMap, 0x0002B35D, 0x0002B52C },
	{ lolLevelShpList, 0x00032826, 0x000328A5 },
	{ lolLevelDatList, 0x000328A5, 0x000329A4 },
	{ lolCompassDefs, 0x000286C4, 0x000287C4 },

	{ lolDscUnk1, 0x00032017, 0x0003203B },
	{ lolDscShapeIndex1, 0x0003203B, 0x0003205F },
	{ lolDscShapeIndex2, 0x0003205F, 0x00032069 },
	{ lolDscScaleWidthData, 0x00032069, 0x000320B1 },
	{ lolDscScaleHeightData, 0x000320B1, 0x000320F9 },
	{ lolDscX, 0x000320F9, 0x00032141 },
	{ lolDscY, 0x00032141, 0x00032165 },
	{ lolDscTileIndex, 0x00032165, 0x00032177 },
	{ lolDscUnk2, 0x00032177, 0x0003218E },
	{ lolDscDoorShapeIndex, 0x0003218E, 0x000321A5 },
	{ lolDscDimData1, 0x00031C03, 0x00031D47 },
	{ lolDscDimData2, 0x00031D47, 0x00031FD0 },
	{ lolDscBlockMap, 0x00031B64, 0x00031B70 },
	{ lolDscDimMap, 0x00031B70, 0x00031B82 },
	{ lolDscDoorScale, 0x00031B82, 0x00031B92 },
	{ lolDscShapeOvlIndex, 0x00031B92, 0x00031BBA },
	{ lolDscDoor4, 0x00031BBA, 0x00031BC2 },
	{ lolDscBlockIndex, 0x00033B53, 0x00033B9B },
	{ lolDscDoor1, 0x0002B550, 0x0002B5D0 },
	{ lolDscDoorX, 0x00027CC0, 0x00028140 },
	{ lolDscDoorY, 0x00028140, 0x000285C0 },

	{ lolScrollXTop, 0x00033D40, 0x00033D4A },
	{ lolScrollYTop, 0x00033D4A, 0x00033D54 },
	{ lolScrollXBottom, 0x00033D54, 0x00033D5E },
	{ lolScrollYBottom, 0x00033D5E, 0x00033D68 },

	{ lolButtonDefs, 0x00028E80, 0x000296AA },
	{ lolButtonList1, 0x000296B0, 0x00029700 },
	{ lolButtonList2, 0x00029700, 0x0002971E },
	{ lolButtonList3, 0x00029720, 0x00029724 },
	{ lolButtonList4, 0x00029730, 0x0002974E },
	{ lolButtonList5, 0x00029750, 0x00029770 },
	{ lolButtonList6, 0x00029770, 0x0002978C },
	{ lolButtonList7, 0x00029790, 0x00029796 },
	{ lolButtonList8, 0x000297A0, 0x000297A4 },

	{ -1, 0, 0 }
};

const Game lolGames[] = {
	{ kLol, EN_ANY, kLolCD, "263998ec600afca1cc7b935c473df670", lolCDFile2},
	GAME_DUMMY_ENTRY
};
