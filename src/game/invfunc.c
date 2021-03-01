#include "game/health.h"
#include "game/inv.h"
#include "game/items.h"
#include "game/text.h"
#include "game/vars.h"
#include "specific/shed.h"
#include "util.h"

#define IT_NAME 0
#define IT_QTY 1

void InitColours()
{
    InvColours[IC_BLACK] = S_Colour(0, 0, 0);
    InvColours[IC_GREY] = S_Colour(64, 64, 64);
    InvColours[IC_WHITE] = S_Colour(255, 255, 255);
    InvColours[IC_RED] = S_Colour(255, 0, 0);
    InvColours[IC_ORANGE] = S_Colour(255, 128, 0);
    InvColours[IC_YELLOW] = S_Colour(255, 255, 0);
    InvColours[IC_DARKGREEN] = S_Colour(0, 128, 0);
    InvColours[IC_GREEN] = S_Colour(0, 255, 0);
    InvColours[IC_CYAN] = S_Colour(0, 255, 255);
    InvColours[IC_BLUE] = S_Colour(0, 0, 255);
    InvColours[IC_MAGENTA] = S_Colour(255, 0, 255);
}

void RingIsOpen(RING_INFO* ring)
{
    if (InventoryMode == INV_TITLE_MODE) {
        return;
    }

    if (!InvRingText) {
        switch (ring->type) {
        case RM_MAIN:
            InvRingText = T_Print(0, 26, 0, "INVENTORY");
            break;

        case RM_OPTION:
            if (InventoryMode == INV_DEATH_MODE) {
                InvRingText = T_Print(0, 26, 0, "GAME OVER");
            } else {
                InvRingText = T_Print(0, 26, 0, "OPTION");
            }
            break;

        case RM_KEYS:
            InvRingText = T_Print(0, 26, 0, "ITEMS");
            break;
        }

        T_CentreH(InvRingText, 1);
    }

    if (InventoryMode == INV_KEYS_MODE || InventoryMode == INV_DEATH_MODE) {
        return;
    }

    if (!InvUpArrow1) {
        if (ring->type == RM_OPTION
            || (ring->type == RM_MAIN && InvKeysObjects)) {
            InvUpArrow1 = T_Print(20, 28, 0, "[");
            InvUpArrow2 = T_Print(-20, 28, 0, "[");
            T_RightAlign(InvUpArrow2, 1);
        }
    }

    if (!InvDownArrow1) {
        if (ring->type == RM_MAIN || ring->type == RM_KEYS) {
            InvDownArrow1 = T_Print(20, -15, 0, "]");
            InvDownArrow2 = T_Print(-20, -15, 0, "]");
            T_BottomAlign(InvDownArrow1, 1);
            T_BottomAlign(InvDownArrow2, 1);
            T_RightAlign(InvDownArrow2, 1);
        }
    }
}

void RingIsNotOpen(RING_INFO* ring)
{
    if (!InvRingText) {
        return;
    }

    T_RemovePrint(InvRingText);
    InvRingText = NULL;

    if (InvUpArrow1) {
        T_RemovePrint(InvUpArrow1);
        T_RemovePrint(InvUpArrow2);
        InvUpArrow1 = NULL;
        InvUpArrow2 = NULL;
    }
    if (InvDownArrow1) {
        T_RemovePrint(InvDownArrow1);
        T_RemovePrint(InvDownArrow2);
        InvDownArrow1 = NULL;
        InvDownArrow2 = NULL;
    }
}

void RingNotActive(INVENTORY_ITEM* inv_item)
{
    if (!InvItemText[IT_NAME]) {
        switch (inv_item->object_number) {
        case O_PUZZLE_OPTION1:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Puzzle1Strings[CurrentLevel]);
            break;

        case O_PUZZLE_OPTION2:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Puzzle2Strings[CurrentLevel]);
            break;

        case O_PUZZLE_OPTION3:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Puzzle3Strings[CurrentLevel]);
            break;

        case O_PUZZLE_OPTION4:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Puzzle4Strings[CurrentLevel]);
            break;

        case O_KEY_OPTION1:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Key1Strings[CurrentLevel]);
            break;

        case O_KEY_OPTION2:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Key2Strings[CurrentLevel]);
            break;

        case O_KEY_OPTION3:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Key3Strings[CurrentLevel]);
            break;

        case O_KEY_OPTION4:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Key4Strings[CurrentLevel]);
            break;

        case O_PICKUP_OPTION1:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Pickup1Strings[CurrentLevel]);
            break;

        case O_PICKUP_OPTION2:
            InvItemText[IT_NAME] =
                T_Print(0, -16, 0, Pickup2Strings[CurrentLevel]);
            break;

        case O_PASSPORT_OPTION:
            break;

        default:
            // XXX: terrible hack
            InvItemText[IT_NAME] = T_Print(0, -16, 0, (char*)inv_item->item_id);
            break;
        }

        if (InvItemText[IT_NAME]) {
            T_BottomAlign(InvItemText[IT_NAME], 1);
            T_CentreH(InvItemText[IT_NAME], 1);
        }
    }

    char temp_text[64];
    int32_t qty = Inv_RequestItem(inv_item->object_number);

    switch (inv_item->object_number) {
    case O_SHOTGUN_OPTION:
        if (!InvItemText[IT_QTY] && !SaveGame[0].bonus_flag) {
            sprintf(temp_text, "%5d A", Lara.shotgun.ammo / SHOTGUN_AMMO_CLIP);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_MAGNUM_OPTION:
        if (!InvItemText[IT_QTY] && !SaveGame[0].bonus_flag) {
            sprintf(temp_text, "%5d B", Lara.magnums.ammo);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_UZI_OPTION:
        if (!InvItemText[IT_QTY] && !SaveGame[0].bonus_flag) {
            sprintf(temp_text, "%5d C", Lara.uzis.ammo);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_SG_AMMO_OPTION:
        if (!InvItemText[IT_QTY]) {
            sprintf(temp_text, "%d", qty * NUM_SG_SHELLS);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_MAG_AMMO_OPTION:
        if (!InvItemText[IT_QTY]) {
            sprintf(temp_text, "%d", Inv_RequestItem(O_MAG_AMMO_OPTION) * 2);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_UZI_AMMO_OPTION:
        if (!InvItemText[IT_QTY]) {
            sprintf(temp_text, "%d", Inv_RequestItem(O_UZI_AMMO_OPTION) * 2);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_MEDI_OPTION:
        HealthBarTimer = 40;
        DrawHealthBar();
        if (!InvItemText[IT_QTY] && qty > 1) {
            sprintf(temp_text, "%d", qty);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_BIGMEDI_OPTION:
        HealthBarTimer = 40;
        DrawHealthBar();
        if (!InvItemText[IT_QTY] && qty > 1) {
            sprintf(temp_text, "%d", qty);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;

    case O_KEY_OPTION1:
    case O_KEY_OPTION2:
    case O_KEY_OPTION3:
    case O_KEY_OPTION4:
    case O_LEADBAR_OPTION:
    case O_PICKUP_OPTION1:
    case O_PICKUP_OPTION2:
    case O_PUZZLE_OPTION1:
    case O_PUZZLE_OPTION2:
    case O_PUZZLE_OPTION3:
    case O_PUZZLE_OPTION4:
    case O_SCION_OPTION:
        if (!InvItemText[IT_QTY] && qty > 1) {
            sprintf(temp_text, "%d", qty);
            MakeAmmoString(temp_text);
            InvItemText[IT_QTY] = T_Print(64, -56, 0, temp_text);
            T_BottomAlign(InvItemText[IT_QTY], 1);
            T_CentreH(InvItemText[IT_QTY], 1);
        }
        break;
    }
}

void RingActive()
{
    if (InvItemText[IT_NAME]) {
        T_RemovePrint(InvItemText[IT_NAME]);
        InvItemText[IT_NAME] = NULL;
    }
    if (InvItemText[IT_QTY]) {
        T_RemovePrint(InvItemText[IT_QTY]);
        InvItemText[IT_QTY] = NULL;
    }
}

int32_t Inv_AddItem(int32_t item_num)
{
    int32_t item_num_option = Inv_GetItemOption(item_num);

    for (int i = 0; i < InvMainObjects; i++) {
        INVENTORY_ITEM* inv_item = InvMainList[i];
        if (inv_item->object_number == item_num_option) {
            InvMainQtys[i]++;
            return 1;
        }
    }

    for (int i = 0; i < InvKeysObjects; i++) {
        INVENTORY_ITEM* inv_item = InvKeysList[i];
        if (inv_item->object_number == item_num_option) {
            InvKeysQtys[i]++;
            return 1;
        }
    }

    switch (item_num) {
    case O_GUN_ITEM:
    case O_GUN_OPTION:
        Inv_InsertItem(&IPistolsOption);
        return 1;

    case O_SHOTGUN_ITEM:
    case O_SHOTGUN_OPTION:
        for (int i = Inv_RequestItem(O_SG_AMMO_ITEM); i > 0; i--) {
            Inv_RemoveItem(O_SG_AMMO_ITEM);
            Lara.shotgun.ammo += SHOTGUN_AMMO_QTY;
        }
        Lara.shotgun.ammo += SHOTGUN_AMMO_QTY;
        Inv_InsertItem(&IShotgunOption);
        GlobalItemReplace(O_SHOTGUN_ITEM, O_SG_AMMO_ITEM);
        return 0;

    case O_MAGNUM_ITEM:
    case O_MAGNUM_OPTION:
        for (int i = Inv_RequestItem(O_MAG_AMMO_ITEM); i > 0; i--) {
            Inv_RemoveItem(O_MAG_AMMO_ITEM);
            Lara.magnums.ammo += MAGNUM_AMMO_QTY;
        }
        Lara.magnums.ammo += MAGNUM_AMMO_QTY;
        Inv_InsertItem(&IMagnumOption);
        GlobalItemReplace(O_MAGNUM_ITEM, O_MAG_AMMO_ITEM);
        return 0;

    case O_UZI_ITEM:
    case O_UZI_OPTION:
        for (int i = Inv_RequestItem(O_UZI_AMMO_ITEM); i > 0; i--) {
            Inv_RemoveItem(O_UZI_AMMO_ITEM);
            Lara.uzis.ammo += UZI_AMMO_QTY;
        }
        Lara.uzis.ammo += UZI_AMMO_QTY;
        Inv_InsertItem(&IUziOption);
        GlobalItemReplace(O_UZI_ITEM, O_UZI_AMMO_ITEM);
        return 0;

    case O_SG_AMMO_ITEM:
    case O_SG_AMMO_OPTION:
        if (Inv_RequestItem(O_SHOTGUN_ITEM)) {
            Lara.shotgun.ammo += SHOTGUN_AMMO_QTY;
        } else {
            Inv_InsertItem(&IShotgunAmmoOption);
        }
        return 0;

    case O_MAG_AMMO_ITEM:
    case O_MAG_AMMO_OPTION:
        if (Inv_RequestItem(O_MAGNUM_ITEM)) {
            Lara.magnums.ammo += MAGNUM_AMMO_QTY;
        } else {
            Inv_InsertItem(&IMagnumAmmoOption);
        }
        return 0;

    case O_UZI_AMMO_ITEM:
    case O_UZI_AMMO_OPTION:
        if (Inv_RequestItem(O_UZI_ITEM)) {
            Lara.uzis.ammo += UZI_AMMO_QTY;
        } else {
            Inv_InsertItem(&IUziAmmoOption);
        }
        return 0;

    case O_MEDI_ITEM:
    case O_MEDI_OPTION:
        Inv_InsertItem(&IMediOption);
        return 1;

    case O_BIGMEDI_ITEM:
    case O_BIGMEDI_OPTION:
        Inv_InsertItem(&IBigMediOption);
        return 1;

    case O_PUZZLE_ITEM1:
    case O_PUZZLE_OPTION1:
        Inv_InsertItem(&IPuzzle1Option);
        return 1;

    case O_PUZZLE_ITEM2:
    case O_PUZZLE_OPTION2:
        Inv_InsertItem(&IPuzzle2Option);
        return 1;

    case O_PUZZLE_ITEM3:
    case O_PUZZLE_OPTION3:
        Inv_InsertItem(&IPuzzle3Option);
        return 1;

    case O_PUZZLE_ITEM4:
    case O_PUZZLE_OPTION4:
        Inv_InsertItem(&IPuzzle4Option);
        return 1;

    case O_LEADBAR_ITEM:
    case O_LEADBAR_OPTION:
        Inv_InsertItem(&ILeadBarOption);
        return 1;

    case O_KEY_ITEM1:
    case O_KEY_OPTION1:
        Inv_InsertItem(&IKey1Option);
        return 1;

    case O_KEY_ITEM2:
    case O_KEY_OPTION2:
        Inv_InsertItem(&IKey2Option);
        return 1;

    case O_KEY_ITEM3:
    case O_KEY_OPTION3:
        Inv_InsertItem(&IKey3Option);
        return 1;

    case O_KEY_ITEM4:
    case O_KEY_OPTION4:
        Inv_InsertItem(&IKey4Option);
        return 1;

    case O_PICKUP_ITEM1:
    case O_PICKUP_OPTION1:
        Inv_InsertItem(&IPickup1Option);
        return 1;

    case O_PICKUP_ITEM2:
    case O_PICKUP_OPTION2:
        Inv_InsertItem(&IPickup2Option);
        return 1;

    case O_SCION_ITEM:
    case O_SCION_ITEM2:
    case O_SCION_OPTION:
        Inv_InsertItem(&IScionOption);
        return 1;
    }

    return 0;
}

void Inv_InsertItem(INVENTORY_ITEM* inv_item)
{
    int n;

    if (inv_item->inv_pos < 100) {
        for (n = 0; n < InvMainObjects; n++) {
            if (InvMainList[n]->inv_pos > inv_item->inv_pos) {
                break;
            }
        }

        if (n == InvMainObjects) {
            InvMainList[InvMainObjects] = inv_item;
            InvMainQtys[InvMainObjects] = 1;
            InvMainObjects++;
        } else {
            for (int i = InvMainObjects; i > n - 1; i--) {
                InvMainList[i + 1] = InvMainList[i];
                InvMainQtys[i + 1] = InvMainQtys[i];
            }
            InvMainList[n] = inv_item;
            InvMainQtys[n] = 1;
            InvMainObjects++;
        }
    } else {
        for (n = 0; n < InvKeysObjects; n++) {
            if (InvKeysList[n]->inv_pos > inv_item->inv_pos) {
                break;
            }
        }

        if (n == InvKeysObjects) {
            InvKeysList[InvKeysObjects] = inv_item;
            InvKeysQtys[InvKeysObjects] = 1;
            InvKeysObjects++;
        } else {
            for (int i = InvKeysObjects; i > n - 1; i--) {
                InvKeysList[i + 1] = InvKeysList[i];
                InvKeysQtys[i + 1] = InvKeysQtys[i];
            }
            InvKeysList[n] = inv_item;
            InvKeysQtys[n] = 1;
            InvKeysObjects++;
        }
    }
}

int32_t Inv_RequestItem(int item_num)
{
    int32_t item_num_option = Inv_GetItemOption(item_num);

    for (int i = 0; i < InvMainObjects; i++) {
        if (InvMainList[i]->object_number == item_num_option) {
            return InvMainQtys[i];
        }
    }

    for (int i = 0; i < InvKeysObjects; i++) {
        if (InvKeysList[i]->object_number == item_num_option) {
            return InvKeysQtys[i];
        }
    }

    return 0;
}

void T1MInjectGameInvFunc()
{
    INJECT(0x0041FEF0, InitColours);
    INJECT(0x00420000, RingIsOpen);
    INJECT(0x00420150, RingIsNotOpen);
    INJECT(0x004201D0, RingNotActive);
    INJECT(0x00420980, RingActive);
    INJECT(0x004209C0, Inv_AddItem);
    INJECT(0x004210D0, Inv_InsertItem);
    INJECT(0x00421200, Inv_RequestItem);
}