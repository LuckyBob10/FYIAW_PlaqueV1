#define siStripLedCount 31
#define siStrip1DataPin 0
#define siStrip2DataPin 1
#define iPixels siStripLedCount * 2

bool
  bDebugLed = false,
  bEffect[] = {false, false, false},
  bEffectShortTrigger = false,
  bEffectMedTrigger = false,
  bEffectLongTrigger = true
;

uint8_t
  iStripBrightnessLow = 16,
  iStripBrightnessHigh = 255,
  iNumEffects = 17,
  iNumPalettes = 10,
  iNumPixelMaps = 8,
  
  iFrameTimeout = 10,
  iStartPixelTimeout = 40,
  iPalettePosTimeout = 20,
  iHueTimeout = 40,

  iStartPixelTimeoutOptions[] = {5, 10, 20, 40, 80, 120},
  iPalettePosTimeoutOptions[] = {5, 10, 20, 40, 80},
  iHueTimeoutOptions[] = {20, 40},
  iPaletteAdvanceOptions[] = {1, 2, 3, 5, 7},
  
  iCurEffect = random(0, iNumEffects + 1),
  iCurPalette = random(0, iNumPalettes + 1),
  iCurPixelMap = random(0, iNumPixelMaps + 1),
  iCurStartPixel = 0,
  iCurHue = 0,
  iCurPalettePos = 0,
  iPaletteAdvance = 1,
  iStripBrightness = iStripBrightnessLow
;

uint16_t
  iRandomizeMin = 10000,
  iRandomizeMax = 30000,
  iRandomizeTimeout = random(iRandomizeMin, iRandomizeMax),
  iDebugLedTimeout = 500,
  iEffectShortTimeout = 50,
  iEffectMedTimeout = 250,
  iEffectLongTimeout = 1000,
  iEffect[] = {0, 0, 0}
;

elapsedMillis
  mRandomize,
  mFrame,
  mStartPixel,
  mPalettePos,
  mHue,
  mEffectShort,
  mEffectMed,
  mEffectLong,
  mDebugLed
;


CRGBPalette16 cStripPalette;
TBlendType cStripBlend;
