// ----------------------------------------------------------------------------
// BugsTerminals.c
// ----------------------------------------------------------------------------

#include "BugsTerminals.h"

// static char *VB_Name = "modBugTerminal";

// --- Option Explicit

long GetTickCount();

byte *TerminalState;
int TerminalMaxCycles;
#define aniTerminal 			(0x80)

// ==========================================================================
//                              SUBROUTINE
// Animate bugs
// ==========================================================================

int subAnimateBugs(int si)
{
  int subAnimateBugs;

  // int ax, bx, cx, dx, di;
  // int ah, bh, ch, dh, al, bl, cl, dl;
  int cx;
  int bl;

  if (fiBug != LowByte(PlayField16[si]))
    return subAnimateBugs;

  if (0 != (TimerVar & 3))
    return subAnimateBugs;

  bl = SgnHighByte(PlayField16[si]); // get and increment sequence#
  bl = bl + 1;
  if (bl >= 0xE)
  {
    bl = subGetRandomNumber(); // generate new random number
    bl = -((bl & 0x3F) + 0x20);
  }

  MovHighByte(&PlayField16[si], bl); // save sequence#
  if (bl < 0) // bug sleeps / is inactive
    return subAnimateBugs;

  // now the bug is active! Beware Murphy!
  if ((ByteMask && PlayField16[si - FieldWidth - 1]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si - FieldWidth]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si - FieldWidth + 1]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si - 1]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si + 1]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si + FieldWidth - 1]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si + FieldWidth]) == fiMurphy)
    goto markPlaySound;

  if ((ByteMask && PlayField16[si + FieldWidth + 1]) == fiMurphy)
    goto markPlaySound;

  goto markDisplay;

markPlaySound:
  subSoundFXBug(); // play dangerous sound

markDisplay:
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  cx = aniBug[bl];
  StretchedSprites.BltEx(GetStretchX(si), GetStretchY(si), cx);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  return subAnimateBugs;
} // subAnimateBugs

// ==========================================================================
//                              SUBROUTINE
// Animate terminals
// ==========================================================================
int subAnimateTerminals(int si)
{
  int subAnimateTerminals;

  // int bl, ax, al, X, Y;
  int bl, al, X, Y;

  if (LowByte(PlayField16[si]) != fiTerminal)
    return subAnimateTerminals;

  bl = HighByte(PlayField16[si]);
  if ((bl & 0x80) == 0x80)
    bl = (bl | 0xFF00);

  bl = bl + 1;
  if (bl <= 0)
  {
    MovHighByte(&PlayField16[si], bl);
    return subAnimateTerminals;
  }

  bl = -(subGetRandomNumber() & TerminalMaxCycles); // generate new random number
  MovHighByte(&PlayField16[si], bl); // save new sequence#
  bl = TerminalState[si] + 1;
  if (bl == 8)
  {
    bl = 0;
  }
  else if (15 < bl)
  {
    bl = 8;
  }

  TerminalState[si] = bl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  al = aniTerminal + bl;
  X = GetStretchX(si);
  Y = GetStretchY(si);
  StretchedSprites.BltEx(X, Y, al);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  return subAnimateTerminals;
} // subAnimateElectrons

// ==========================================================================
//                              SUBROUTINE
// Randomize random number generator
// ==========================================================================

int subRandomize()
{
  int subRandomize;

  long Tick, Tmp;

  Tick = GetTickCount();
  Tmp = ((Tick ^ (long)(Tick / (1 << 16))) & 0xFFFF);
  RandomSeed = 0x7FFF & Tmp;
  if ((Tmp & 0x8000) != 0)
    RandomSeed = RandomSeed | 0x8000;

  return subRandomize;
} // subRandomize


// ==========================================================================
//                              SUBROUTINE
// Generate new random number, first method (see also sub_g_8580)
// ==========================================================================

int subGetRandomNumber()
{
  int subGetRandomNumber;

  long Tmp, RSeed;

  RSeed = (long)(0x7FFF & RandomSeed);
  if (0x8000 == (RandomSeed & 0x8000))
    RSeed = RSeed | 0x8000;

  Tmp = 0xFFFF & (((0x5E5 * RandomSeed) & 0xFFFF) + 0x31);
  RandomSeed = 0x7FFF & Tmp;
  if ((Tmp & 0x8000) != 0)
    RandomSeed = RandomSeed | 0x8000;

  subGetRandomNumber = Tmp / 2;
  //  Mov ax, randomseed
  //  Mov bx, &H5E5
  //  mul bx                          ' dx:ax = reg * ax
  //  Add ax, &H31
  //  Mov randomseed, ax
  //  shr ax,1

  return subGetRandomNumber;
} // subGetRandomNumber
