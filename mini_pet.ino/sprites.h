#pragma once

// each letter is one pixel:  . = see-through  K = outline  B = body  L = shine
// your drawing! K = black outline, B = gold, M = mid gold, S = dark gold, W = white
const char* PET_BODY[16] = {
  "................",
  "..B....KK.......",
  ".WBS..KWWK......",
  "..S...KWBK......",
  ".....KWBBMK.....",
  "K.KKKWBBBBMKKK.K",
  ".KWWWWBBBBBBBSK.",
  "..KWBBBBBBBBSK..",
  "...KWBBBBBBSK.B.",
  "....KWBBBBSK.WBS",
  "...KWBBBBBBSK.S.",
  "...KBBBMMBBSK...",
  "..KBBBMKKMMBBK..",
  "..KMMKK..KKSSK..",
  ".KMKK......KKSK.",
  "K.K..........K.K"
};

const char* HEART[6] = {
  ".HH.HH.",
  "HHHHHHH",
  "HHHHHHH",
  ".HHHHH.",
  "..HHH..",
  "...H..."
};

const char* POOP[7] = {
  "...PP...",
  "..PPPP..",
  "...PPP..",
  ".PPPPPP.",
  "PPPPPPPP",
  "PPPPPPPP",
  ".PPPPPP."
};

// the ghost that floats out when star dies (G = outline, W = white, K = eyes)
const char* GHOST[10] = {
  "...GGGG...",
  "..GWWWWG..",
  ".GWWWWWWG.",
  ".GWKWWKWG.",
  ".GWWWWWWG.",
  ".GWWKKWWG.",
  ".GWWWWWWG.",
  ".GWWWWWWG.",
  ".GWGWWGWG.",
  ".GG.GG.GG."
};