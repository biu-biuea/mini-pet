#pragma once

// colors: red, green, blue from 0 to 255
#define COL(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

const uint16_t C_BG        = COL(255, 250, 240);   // warm white background
const uint16_t C_TEXT      = COL(70, 60, 80);
const uint16_t C_OUTLINE   = COL(0, 0, 0);         // black outline + eyes
const uint16_t C_BODY      = COL(255, 197, 0);     // gold
const uint16_t C_MID       = COL(228, 156, 0);     // mid gold
const uint16_t C_SHADE     = COL(200, 137, 0);     // dark gold
const uint16_t C_LIGHT     = COL(255, 240, 160);   // shine
const uint16_t C_CHEEK     = COL(255, 110, 150);
const uint16_t C_TEAR      = COL(80, 160, 255);
const uint16_t C_POOP      = COL(140, 90, 50);
const uint16_t C_HEART     = COL(255, 60, 90);
const uint16_t C_GHOST     = COL(250, 251, 255);   // ghost white
const uint16_t C_GHOSTLINE = COL(180, 185, 225);   // ghost outline
const uint16_t C_BARBG     = COL(230, 225, 225);
const uint16_t C_FOOD      = COL(255, 150, 60);
const uint16_t C_FUN       = COL(120, 200, 80);
const uint16_t C_REST      = COL(150, 120, 230);