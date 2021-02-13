#ifndef TR1MAIN_GAME_DATA_H
#define TR1MAIN_GAME_DATA_H

#include "game/types.h"
#include "util.h"

// clang-format off
#define cd_drive                VAR_I_(0x0045A010, char, '.')
#define DEMO                    VAR_I_(0x0045F1C0, uint32_t, 0)
#define dword_45A1F0            VAR_U_(0x0045A1F0, uint32_t)
#define newpath                 ARRAY_(0x00459F90, char, [128])
#define RoomCount               VAR_U_(0x00462BDC, uint16_t)
#define RoomInfo                VAR_U_(0x00462BE8, ROOM_INFO*)
#define PhdWinMaxX              VAR_I_(0x006CAD00, int32_t, 0)
#define PhdWinMaxY              VAR_I_(0x006CAD10, int32_t, 0)
#define FloorData               VAR_U_(0x0045F1BC, uint16_t*)
#define StringToShow            ARRAY_(0x00456AD0, char, [128])
#define Meshes                  VAR_U_(0x00461F34, uint16_t**)
#define Objects                 ARRAY_(0x0045F9E0, OBJECT_INFO, [NUMBER_OBJECTS])
#define StaticObjects           ARRAY_(0x00462660, STATIC_INFO, [])
#define LevelItemCount          VAR_U_(0x0045A0E0, int32_t)
#define Items                   VAR_U_(0x00462CEC, ITEM_INFO*)
#define GameAllocMemPointer     VAR_U_(0x0045E32C, uint32_t)
#define GameAllocMemUsed        VAR_U_(0x0045E330, uint32_t)
#define GameAllocMemFree        VAR_U_(0x0045E334, uint32_t)
#define GameMemoryPointer       VAR_U_(0x0045A034, uint32_t)
#define GameMemorySize          VAR_U_(0x0045EEF8, uint32_t)
#define CurrentLevel            VAR_U_(0x00453C4C, uint32_t)
#define Lara                    VAR_U_(0x0045ED80, LARA_INFO)
#define LaraItem                VAR_U_(0x0045EE6C, ITEM_INFO*)
#define LevelNames              ARRAY_(0x00453648, const char*, [NUMBER_OF_LEVELS])
#define LevelTitles             ARRAY_(0x00453DF8, const char*, [NUMBER_OF_LEVELS])
#define SecretTotals            ARRAY_(0x00453CB0, __int8, [MAX_SECRETS])
#define ResetFlag               VAR_I_(0x00459F50, int32_t, 0)
#define Input                   VAR_U_(0x0045EEF4, int)
#define HiRes                   VAR_I_(0x00459F64, int32_t, 0)
#define Effects                 VAR_U_(0x0045EE70, FX_INFO*)
#define NextItemActive          VAR_U_(0x0045EE78, int16_t)
#define NextFxFree              VAR_U_(0x0045EE74, int16_t)
#define NextFxActive            VAR_U_(0x0045EE7A, int16_t)
#define SaveGame                ARRAY_(0x0045B9C0, SAVEGAME_INFO, [2])
#define BaddieSlots             VAR_U_(0x0045ED64, CREATURE_INFO*)
#define SlotsUsed               VAR_U_(0x0045A1F8, int)
#define NumberBoxes             VAR_U_(0x00462DA0, int)
#define Pickups                 ARRAY_(0x0045EF00, DISPLAYPU, [NUM_PU])
#define OverlayFlag             VAR_U_(0x004546B4, int32_t)
#define HealthBarTimer          VAR_U_(0x0045A0E4, int32_t)
#define OldGameTimer            VAR_U_(0x0045A028, int32_t)
#define OldHitPoints            VAR_U_(0x0045A02C, int32_t)
#define PhdLeft                 VAR_U_(0x00695190, int32_t)
#define PhdBottom               VAR_U_(0x00695188, int32_t)
#define PhdRight                VAR_U_(0x006E80E0, int32_t)
#define PhdTop                  VAR_U_(0x0068D380, int32_t)
#define PhdWinWidth             VAR_U_(0x006CADD4, int32_t)
#define PhdWinHeight            VAR_U_(0x0068F3A8, int32_t)
#define AmmoText                VAR_U_(0x0045A030, TEXTSTRING*)
#define Rand1                   VAR_I_(0x00453CC0, int32_t, 0xD371F947)
#define Rand2                   VAR_I_(0x00453CC4, int32_t, 0xD371F947)
#define ValidLevels             ARRAY_(0x00453C80, int16_t, [])
#define FrameCount              VAR_I_(0x00459F58, int32_t, 0)
#define AnimationRate           VAR_I_(0x004534E0, int32_t, 0x8000)
#define InventoryExtraData      ARRAY_(0x0045A080, int32_t, [8])
#define LevelComplete           VAR_U_(0x0045A014, int32_t)
#define KeyData                 VAR_U_(0x0045B998, KEYSTUFF*)
#define CDTrack                 VAR_I_(0x004534DC, int16_t, -1)
#define Camera                  VAR_U_(0x00462D20, CAMERA_INFO)
#define CameraUnderwater        VAR_U_(0x00462BEC, int32_t)
#define PhdMatrixPtr            VAR_U_(0x006CAD14, int32_t)
#define Anims                   VAR_U_(0x00462574, ANIM_STRUCT*)
#define FlipTimer               VAR_I_(0x00459F54, int32_t, 0)
#define FlipEffect              VAR_I_(0x004534E4, int32_t, -1)
#define ModeLock                VAR_I_(0x00459F70, int32_t, 0)
#define IsSoftwareRenderer      VAR_U_(0x00463610, int32_t)
#define AppSettings             VAR_U_(0x0045A240, uint32_t)
#define JoyXPos                 VAR_U_(0x0045B958, int32_t)
#define JoyYPos                 VAR_U_(0x0045B95C, int32_t)
#define KeyData                 VAR_U_(0x0045B998, KEYSTUFF*)
// clang-format on

#endif
