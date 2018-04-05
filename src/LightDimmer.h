/*
 * Light Dimmer Library for Arduino
 *
 * Copyright Jean-Luc Béchennec 2018
 *
 * This software is distributed under the GNU Public Licence v2 (GPLv2)
 *
 * Please read the LICENCE file
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __LIGHT_DIMMER__
#define __LIGHT_DIMMER__

#include "Arduino.h"

class LightDimmer
{
  private:
    enum { LD_OFF, LD_ON, LD_RISING, LD_FALLING };

    uint8_t  mState;
    uint8_t  mMax;
    uint16_t mRiseTime;
    uint16_t mFallTime;
    uint16_t mOnTime;
    uint16_t mPeriod;
    uint32_t mNextEventDate;

    LightDimmer *mNext;
    static LightDimmer *sLightList;

    void updateState();
    virtual void updateOutput();

  protected:
    uint8_t  mValue;
    uint8_t  mPin:6;
    bool     mBlink:1;
    uint8_t  mOff:1;

  public:
    LightDimmer();
    void begin(const uint8_t inPin, const uint8_t inOn);
    void setMax(const uint8_t inMax) { mMax = inMax; };
    void setFadingTime(const uint16_t inFallTime) { mFallTime = inFallTime > 0 ? inFallTime : 1; };
    void setBrighteningTime(const uint16_t inRiseTime) { mRiseTime = inRiseTime > 0 ? inRiseTime : 1; };
    void setOnTime(const uint16_t inOnTime) { mOnTime = inOnTime; };
    void setPeriod(const uint16_t inPeriod) { mPeriod = inPeriod; };
    void on();
    void off();
    void startBlink();
    void stopBlink()     { mBlink = false; };
    bool isOn()          { return (mState == LD_ON); }
    bool isOff()         { return (mState == LD_OFF); }
    bool isFading()      { return (mState == LD_FALLING); }
    bool isBrightening() { return (mState == LD_RISING); }

    static void update();
};

class LightDimmerSoft : public LightDimmer
{
  private:
    uint8_t mDuty;

    virtual void updateOutput();

  public:
    LightDimmerSoft() : LightDimmer() {}

};

#endif
