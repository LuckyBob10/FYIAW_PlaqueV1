#include "FastLED.h"
#include "vars.h"
#include "palettes.h"
#include "pixelmaps.h"
#include "functions.h"

CRGB Strip[iPixels];
  
void setup() {
  randomSeed(analogRead(2));
  FastLED.addLeds<WS2811, siStrip1DataPin, GRB>(Strip, 0, siStripLedCount);
  FastLED.addLeds<WS2811, siStrip2DataPin, GRB>(Strip, siStripLedCount, siStripLedCount);
  FastLED.setBrightness(iStripBrightness);

  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  cStripPalette = pPalettes[iCurPalette];
  cStripBlend = LINEARBLEND;
  delay(500);
}

void loop() {
  //Toggle debug led and check button
  if (mDebugLed > iDebugLedTimeout) {
    bDebugLed = !bDebugLed;
    digitalWrite(13, bDebugLed);
    uint8_t iOldStripBrightness = iStripBrightness;
    if (digitalRead(3) == LOW) {
      iStripBrightness = iStripBrightnessLow;
    }
    else {
      iStripBrightness = iStripBrightnessHigh;
    }
    if (iStripBrightness != iOldStripBrightness) {
      FastLED.setBrightness(iStripBrightness);
    }
    mDebugLed = 0;
  }

  //Advance Pixel
  if (mStartPixel > iStartPixelTimeout) {
    iCurStartPixel = Advance8BitVal(iCurStartPixel, iPixels);
    mStartPixel = 0;
  }

  //Advance palette position
  if (mPalettePos > iPalettePosTimeout) {
    iCurPalettePos = Advance8BitVal(iCurPalettePos, 255, iPaletteAdvance);
    mPalettePos = 0;
  }

  //Advance Hue
  if (mHue > iHueTimeout) {
    iCurHue = Advance8BitVal(iCurHue);
    mHue = 0;
  }

  //Randomize!
  if (mRandomize > iRandomizeTimeout) {
    //Reset all variables
    iEffect[0] = 0;
    iEffect[1] = 0;
    iEffect[2] = 0;
    bEffect[0] = false;
    bEffect[1] = false;
    bEffect[2] = false;
    
    uint8_t iChangeCount = random(1, 7);
    Serial.print("- Randomizing ");
    Serial.print(iChangeCount);
    Serial.println(" item(s).");
    int iChangeItems[] = {0, 1, 2, 3, 4, 5, 6};
    scrambleArray(iChangeItems, 0, 7);
    Serial.print("Change array: ");
    for (uint8_t i=0; i<7; i++) {
      Serial.print(iChangeItems[i]);
    }
    Serial.println();
    for (uint8_t i=0; i<iChangeCount; i++) {
      uint8_t iTemp;
      switch (iChangeItems[i]) {
        case 0:
          //iStartPixelTimeoutOptions
          iTemp = GetUniqueRandom8Bit(iStartPixelTimeout, 0, sizeof(iStartPixelTimeoutOptions) - 1);
          iStartPixelTimeout = iStartPixelTimeoutOptions[iTemp];
          Serial.print("Pixel advance timeout: #");
          Serial.print(iTemp);
          Serial.print(", ");
          Serial.println(iStartPixelTimeout);
          break;
        case 1:
          //iPalettePosTimeoutOptions
          iTemp = GetUniqueRandom8Bit(iPalettePosTimeout, 0, sizeof(iPalettePosTimeoutOptions) - 1);
          iPalettePosTimeout = iPalettePosTimeoutOptions[iTemp];
          Serial.print("Palette position timeout: #");
          Serial.print(iTemp);
          Serial.print(", ");
          Serial.println(iPalettePosTimeout);
          break;
        case 2:
          //iPaletteAdvanceOptions
          iTemp = GetUniqueRandom8Bit(iPaletteAdvance, 0, sizeof(iPaletteAdvanceOptions) - 1);
          iPaletteAdvance = iPaletteAdvanceOptions[iTemp];
          Serial.print("Palette advance speed: #");
          Serial.print(iTemp);
          Serial.print(", ");
          Serial.println(iPaletteAdvance);
          break;
        case 3:
          //iNumEffects
          Serial.print("Effect: ");
          Serial.println(iCurEffect);
          iCurEffect = GetUniqueRandom8Bit(iCurEffect, 0, iNumEffects);
          break;
        case 4:
          //iNumPalettes
          Serial.print("Palette: ");
          Serial.println(iCurPalette);
          iCurPalette = GetUniqueRandom8Bit(iCurPalette, 0, iNumPalettes);
          cStripPalette = pPalettes[iCurPalette];
          break;
        case 5:
          //iNumPixelMaps
          Serial.print("Pixel map: ");
          Serial.println(iCurPixelMap);
          iCurPixelMap = GetUniqueRandom8Bit(iCurPixelMap, 0, iNumPixelMaps);
          break;
        case 6:
          //Blend
          Serial.print("Blend mode: ");
          if (cStripBlend == NOBLEND) {
            Serial.println("linear blend");
            cStripBlend = LINEARBLEND;
          }
          else {
            Serial.println("no blend");
            cStripBlend = NOBLEND;
          }
          break;
      }
    }
    iRandomizeTimeout = random(iRandomizeMin, iRandomizeMax);
    Serial.print("Next change in ");
    Serial.print(iRandomizeTimeout);
    Serial.println("ms.");
    Serial.println();
    mRandomize = 0;
  }
  

  //Display Frame
  if (mFrame > iFrameTimeout) {

    //FORCE EFFECTS FOR TESTING
    //iCurEffect = 12;
    //iCurPixelMap = 0;
    //cStripPalette = pPalettes[2];
    //cStripBlend = NOBLEND;
    //cStripBlend = LINEARBLEND;


    //Populate temporary variables for this frame
    uint8_t
      iTempStartPixel = iCurStartPixel,
      iTempPalettePos = iCurPalettePos
    ;

    //Update timers
    if (mEffectShort > iEffectShortTimeout) {
      bEffectShortTrigger = true;
      mEffectShort = 0;
    }
    if (mEffectMed > iEffectMedTimeout) {
      bEffectMedTrigger = true;
      mEffectMed = 0;
    }
    if (mEffectLong > iEffectLongTimeout) {
      bEffectLongTrigger = true;
      mEffectLong = 0;
    }

    //Render effect for frame
    switch (iCurEffect) {
      case 0:
        //Full strip rainbow
        for (uint8_t i=0; i<iPixels; i++) {
          Strip[iPixelMap[iCurPixelMap][i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempPalettePos = Advance8BitVal(iTempPalettePos, 255, iPaletteAdvance);
        }
        break;

      case 1:
        //Crawl six pixels
        fill_solid(Strip, iPixels, CRGB::Black);
        for (uint8_t i=0; i<6; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      case 2:
        //Flash whole strip - med
        if (bEffectMedTrigger) {
          bEffect[0] = !bEffect[0];
        }
        if (bEffect[0]) {
          fill_solid(Strip, iPixels, ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend));
        }
        else {
          fill_solid(Strip, iPixels, CRGB::Black);
        }
        break;

      case 3:
        //Fill whole strip
        fill_solid(Strip, iPixels, ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend));
        break;

      case 4:
        //Fill half strip w/ crawl
        fill_solid(Strip, iPixels, CRGB::Black);
        for (uint8_t i=0; i<iPixels/2; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempPalettePos = Advance8BitVal(iTempPalettePos, 255, iPaletteAdvance);
        }
        //Fade ends
        for (uint8_t i=0; i<4; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] %= 128 / (4-i);
          iTempStartPixel = LimitPixel(iCurStartPixel + iPixels/2 - i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] %= 128 / (4-i);
        }
        break;

      case 5:
        //Crawl from inside/outside
        if (bEffectShortTrigger) {
          iEffect[0]++;
          if (iEffect[0] > iPixels/2) {
            bEffect[0] = !bEffect[0];
            iEffect[0] = 0;
          }
        }
        if (bEffect[0]) {
          //Outside in
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            iTempPalettePos = Advance8BitVal(iTempPalettePos, 255, iPaletteAdvance);
          }
        }
        else {
          //Inside out
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][iPixels/2 + i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels/2 - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          }
        }
        break;

      case 6:
        //Crawl from inside/outside w/ blackout
        if (bEffectShortTrigger) {
          iEffect[0]++;
          if (iEffect[0] > iPixels/2) {
            bEffect[0] = !bEffect[0];
            iEffect[0] = 0;
            fill_solid(Strip, iPixels, CRGB::Black);
          }
        }
        if (bEffect[0]) {
          //Outside in
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            iTempPalettePos = Advance8BitVal(iTempPalettePos, 255, iPaletteAdvance);
          }
        }
        else {
          //Inside out
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][iPixels/2 + i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels/2 - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          }
        }
        break;
      
      case 7:
        //Crawl from inside/outside w/ blackout
        if (bEffectShortTrigger) {
          iEffect[0]++;
          if (iEffect[0] > iPixels/2) {
            bEffect[0] = !bEffect[0];
            iEffect[0] = 0;
            fill_solid(Strip, iPixels, CRGB::Black);
          }
        }
        if (bEffect[0]) {
          //Outside in
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            iTempPalettePos = Advance8BitVal(iTempPalettePos, 255, iPaletteAdvance);
          }
        }
        else {
          //Inside out
          for (uint8_t i=0; i<iEffect[0]; i++) {
            Strip[iPixelMap[iCurPixelMap][iPixels/2 + i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
            Strip[iPixelMap[iCurPixelMap][iPixels/2 - i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          }
        }
        break;

      case 8:
        //Add random pixels w/ blackout
        if (bEffectLongTrigger) {
          iEffect[0]++;
        }
        if (iEffect[0] > 3) {
          iEffect[0] = 0;
          fill_solid(Strip, iPixels, CRGB::Black);
        }
        if (bEffectLongTrigger) {
          iEffect[0]++;
        }
        if (bEffectShortTrigger) {
          for (uint8_t i=0; i<3; i++) {
            Strip[random(0, iPixels)] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          }
        }
        break;

      case 9:
        //Add blocks of color
        if (bEffectMedTrigger) {
          iTempStartPixel = random(0, iPixels);
          for (uint8_t i=0; i<8; i++) {
            iTempStartPixel = LimitPixel(iTempStartPixel + i);
            Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          }
        }
        if (bEffectShortTrigger) {
          for (uint8_t i=0; i<iPixels; i++) {
            Strip[i].fadeToBlackBy(8);
          }
        }
        break;

      case 10:
        //Crawl with periodic invert
        Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        if (bEffectLongTrigger) {
          iEffect[0]++;
          if (iEffect[0] > 3) {
            iEffect[0] = 0;
            for (uint8_t i=0; i<iPixels; i++) {
              Strip[i] = -Strip[i];
            }
          }
        }
        break;

      case 11:
        //Single color flash and fade
        if (bEffectShortTrigger) {
          for (uint8_t i=0; i<iPixels; i++) {
            Strip[i].fadeToBlackBy(8);
          }
        }        
        if (bEffectLongTrigger) {
          fill_solid(Strip, iPixels, ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend));
        }
        break;

      case 12:
        //Fade in and out
        if (bEffect[0]) {
          if (iEffect[0] > 254) {
            bEffect[0] = false;
          }
          else {
            iEffect[0]++;
          }
        }
        else {
          if (iEffect[0] < 1) {
            bEffect[0] = true;
          }
          else {
            iEffect[0]--;
          }
        }
        fill_solid(Strip, iPixels, ColorFromPalette(cStripPalette, iTempPalettePos, iEffect[0], cStripBlend));
        break;

      case 13:
        //Quadrants
        if (bEffectLongTrigger) {
          uint8_t iOldEffect = iEffect[0];
          for (uint8_t x=0; x<25; x++) {
            iEffect[0] = random(0, 4);
            if (iEffect[0] != iOldEffect) {
              break;
            }
          }
          fill_solid(Strip, iPixels, CRGB::Black);
        }
        for (uint8_t i=0; i<16; i++) {
          Strip[iPixelMap[iCurPixelMap][15*iEffect[0] + i]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      case 14:
        //Double chase
        fill_solid(Strip, iPixels, CRGB::Black);
        for (uint8_t i=0; i<5; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempStartPixel = LimitPixel(iPixels / 2 + iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      case 15:
        //Double inverted chase w/ blackout
        fill_solid(Strip, iPixels, CRGB::Black);
        for (uint8_t i=0; i<5; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempStartPixel = LimitPixel(iPixels - iCurStartPixel - i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = -ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      case 16:
        //Double inverted chase w/ periodic blackout
        if (bEffectLongTrigger) {
          iEffect[0]++;
          if (iEffect[0] > 5) {
            fill_solid(Strip, iPixels, CRGB::Black);
            iEffect[0] = 0;
          }
        }
        for (uint8_t i=0; i<3; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempStartPixel = LimitPixel(iPixels - iCurStartPixel - i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = -ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      case 17:
        //Double chase w/ invert
        fill_solid(Strip, iPixels, CRGB::Black);
        for (uint8_t i=0; i<5; i++) {
          iTempStartPixel = LimitPixel(iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
          iTempStartPixel = LimitPixel(iPixels / 2 + iCurStartPixel + i);
          Strip[iPixelMap[iCurPixelMap][iTempStartPixel]] = -ColorFromPalette(cStripPalette, iTempPalettePos, 255, cStripBlend);
        }
        break;

      //-- End Effect --//
    }

    //Display frame
    FastLED.show();

    //Reset interval timers if necessary
    bEffectShortTrigger = false;
    bEffectMedTrigger = false;
    bEffectLongTrigger = false;
  }
}



