#include "game/data.h"
#include "game/health.h"
#include "game/shell.h"
#include "game/text.h"
#include "mod.h"

void __cdecl DrawGameInfo()
{
    DrawAmmoInfo();
    if (OverlayFlag > 0) {
        DrawHealthBar();
        DrawAirBar();
        DrawPickups();

        if (TR1MConfig.enable_enemy_healthbar && Lara.target) {
            TR1MRenderBar(
                Lara.target->hit_points,
                Objects[Lara.target->object_number].hit_points,
                TRM1_BAR_ENEMY_HEALTH);
        }
    }

    T_DrawText();
}

void __cdecl DrawHealthBar()
{
    int hit_points = LaraItem->hit_points;
    if (hit_points < 0) {
        hit_points = 0;
    } else if (hit_points > LARA_HITPOINTS) {
        hit_points = LARA_HITPOINTS;
    }

    if (OldHitPoints != hit_points) {
        OldHitPoints = hit_points;
        HealthBarTimer = 40;
    }

    if (HealthBarTimer < 0) {
        HealthBarTimer = 0;
    }

    if (HealthBarTimer > 0 || hit_points <= 0 || Lara.gun_status == LG_READY) {
        S_DrawHealthBar(hit_points * 100 / LARA_HITPOINTS);
    }
}

void __cdecl DrawAirBar()
{
    if (Lara.water_status != LARA_UNDERWATER
        && Lara.water_status != LARA_SURFACE) {
        return;
    }

    int air = Lara.air;
    if (air < 0) {
        air = 0;
    } else if (Lara.air > LARA_AIR) {
        air = LARA_AIR;
    }

    S_DrawAirBar(air * 100 / LARA_AIR);
}

void __cdecl DrawAmmoInfo()
{
    char ammostring[80] = "";

    if (Lara.gun_status != LG_READY || OverlayFlag <= 0
        || SaveGame[0].bonus_flag) {
        if (AmmoText) {
            T_RemovePrint(AmmoText);
            AmmoText = 0;
        }
        return;
    }

    switch (Lara.gun_type) {
    case LG_PISTOLS:
        return;
    case LG_MAGNUMS:
        sprintf(ammostring, "%5d B", Lara.magnums.ammo);
        break;
    case LG_UZIS:
        sprintf(ammostring, "%5d C", Lara.uzis.ammo);
        break;
    case LG_SHOTGUN:
        sprintf(ammostring, "%5d A", Lara.shotgun.ammo / SHOTGUN_AMMO_CLIP);
        break;
    default:
        return;
    }

    MakeAmmoString(ammostring);

    if (AmmoText) {
        T_ChangeText(AmmoText, ammostring);
    } else {
        AmmoText = T_Print(-17, 22, 0, ammostring);
        T_RightAlign(AmmoText, 1);
    }
}

void __cdecl MakeAmmoString(char* string)
{
    char* c;

    for (c = string; *c != 0; c++) {
        if (*c == 32) {
            continue;
        } else if (*c - 'A' >= 0) {
            *c += 12 - 'A';
        } else {
            *c += 1 - '0';
        }
    }
}

void __cdecl InitialisePickUpDisplay()
{
    for (int i = 0; i < NUM_PU; i++) {
        Pickups[i].duration = 0;
    }
}

void __cdecl DrawPickups()
{
    int old_game_timer = OldGameTimer;
    OldGameTimer = SaveGame[0].timer;
    int16_t time = SaveGame[0].timer - old_game_timer;

    if (time > 0 && time < 60) {
        int y = PhdWinHeight - PhdWinWidth / 10;
        int x = PhdWinWidth - PhdWinWidth / 10;
        int sprite_width = 4 * (PhdWinWidth / 10) / 3;
        for (int i = 0; i < NUM_PU; i++) {
            DISPLAYPU* pu = &Pickups[i];
            pu->duration -= time;
            if (pu->duration <= 0) {
                pu->duration = 0;
            } else {
                S_DrawUISprite(
                    x, y, TR1MGetOverlayScale(12288), pu->sprnum, 4096);
                x -= sprite_width;
            }
        }
    }
}

void __cdecl AddDisplayPickup(int16_t objnum)
{
    for (int i = 0; i < NUM_PU; i++) {
        if (Pickups[i].duration <= 0) {
            Pickups[i].duration = 75;
            Pickups[i].sprnum = Objects[objnum].mesh_index;
            return;
        }
    }
}

void TR1MInjectHealth()
{
    INJECT(0x0041DD00, DrawGameInfo);
    INJECT(0x0041DEA0, DrawHealthBar);
    INJECT(0x0041DF20, MakeAmmoString);
    INJECT(0x0041DF50, DrawAmmoInfo);
    INJECT(0x0041E0A0, InitialisePickUpDisplay);
    INJECT(0x0041E0C0, AddDisplayPickup);
}