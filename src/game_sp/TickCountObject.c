// ----------------------------------------------------------------------------
// TickCountObject.c
// ----------------------------------------------------------------------------

#include "TickCountObject.h"

// --- VERSION 1.0 CLASS
// --- BEGIN
// ---   MultiUse = -1  'True  // True
// ---   Persistable = 0  'NotPersistable  // NotPersistable
// ---   DataBindingBehavior = 0  'vbNone  // vbNone
// ---   DataSourceBehavior  = 0  'vbNone  // vbNone
// ---   MTSTransactionMode  = 0  'NotAnMTSObject  // NotAnMTSObject
// --- END

// static char *VB_Name = "TickCountObject";
// static boolean VB_GlobalNameSpace = False;
// static boolean VB_Creatable = True;
// static boolean VB_PredeclaredId = False;
// static boolean VB_Exposed = False;
// --- Option Explicit

#define LongMin 			(-(double)2147483648UL) // the "#" sign is a bug of the VB environment AutoFormat function but causes no real problems; don't  worry 'bout it!
#define LongMax 			(2147483647UL)

long GetTickCount();
long QueryPerformanceCounter(currency lpPerformanceCount);
long QueryPerformanceFrequency(currency lpFrequency);

boolean DelayLoopActive;

boolean MPause, bHighPerf;
currency PFreq; // LARGE_INTEGER
double sFactor, msFactor, usFactor;

boolean TickCountObject_Get_Active()
{
  boolean Active;

  Active = DelayLoopActive;

  return Active;
}

boolean TickCountObject_Get_Pause()
{
  boolean Pause;

  Pause = MPause;

  return Pause;
}

void TickCountObject_Let_Pause(boolean NewVal)
{
  MPause = NewVal;
}

void TickCountObject_DelayMS(long MSInterval, boolean DoEventsFlag) // in ms
{
  currency Start;

  Start = TickCountObject_Get_TickNow();
  DelayLoopActive = True;
  do
  {
    if (DoEventsFlag)
      DoEvents();

    if (MSInterval <= TickCountObject_TickDiffMS(Start) && ! MPause)
      break;
  }
  while (1);

  DelayLoopActive = False;
}

// for compatibility with old code:
void TickCountObject_DelayS(long SInterval, boolean DoEventsFlag) // in s
{
  // check if SInterval is less than 25 days ...
  if ((int)(LongMax / 1000) <= SInterval)
  {
    Err.Raise(513, "Delay()", "Value Overflow");
  }
  else
  {
    TickCountObject_DelayMS((long)1000 * SInterval, DoEventsFlag);
  }
}

currency TickCountObject_Get_TickNow()
{
  currency TickNow;

  if (bHighPerf)
  {
    QueryPerformanceCounter(TickNow);
  }
  else
  {
    TickNow = GetTickCount();
  }

  return TickNow;
}

long TickCountObject_TickDiffS(currency TickStart)
{
  long TickDiffS;

  currency NewTick, TD;

  if (bHighPerf)
  {
    QueryPerformanceCounter(NewTick);
    TD = (NewTick - TickStart);
    TickDiffS = sFactor * TD;
  }
  else
  {
    NewTick = GetTickCount();
    if (NewTick < TickStart)
    {
      // Overflow occured and needs to be handled
      TickDiffS = (LongMax - TickStart) + (NewTick - LongMin) + 1;
    }
    else
    {
      TickDiffS = NewTick - TickStart;
    }

    TickDiffS = (int)(TickDiffS / 1000);
  }

  return TickDiffS;
}

long TickCountObject_TickDiffMS(currency TickStart)
{
  long TickDiffMS;

  currency NewTick, TD;

  if (bHighPerf)
  {
    QueryPerformanceCounter(NewTick);
    TD = (NewTick - TickStart);
    TickDiffMS = msFactor * TD;
  }
  else
  {
    NewTick = GetTickCount();
    if (NewTick < TickStart)
    {
      // Overflow occured and needs to be handled
      TickDiffMS = (LongMax - TickStart) + (NewTick - LongMin) + 1;
    }
    else
    {
      TickDiffMS = NewTick - TickStart;
    }
  }

  return TickDiffMS;
}

currency TickCountObject_TickDiffUS(currency TickStart)
{
  currency TickDiffUS;

  currency NewTick, TD;

  if (bHighPerf)
  {
    QueryPerformanceCounter(NewTick);
    TD = (NewTick - TickStart);
    TickDiffUS = usFactor * TD;
  }
  else
  {
    NewTick = GetTickCount();
    if (NewTick < TickStart)
    {
      // Overflow occured and needs to be handled
      TickDiffUS = ((LongMax - TickStart) + (NewTick - LongMin) + 1) * (currency)1000;
    }
    else
    {
      TickDiffUS = (NewTick - TickStart) * (currency)1000;
    }
  }

  return TickDiffUS;
}

#if 0

static void Class_Initialize()
{
  long L;

  bHighPerf = (0 != QueryPerformanceFrequency(PFreq));
  if (bHighPerf)
  {
    sFactor = (double)1 / PFreq;
    msFactor = (double)1000 / PFreq;
    usFactor = (double)1000000 / PFreq;
  }

  DelayLoopActive = False;
  TickCountObject_Let_Pause(False);
}

#endif