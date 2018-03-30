/*
 * Light Dimmer Library for Arduino
 *
 * Copyright Jean-Luc Béchennec 2015
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

class LightDimmer {
  private:
    enum { LD_OFF, LD_ON, LD_RISING, LD_FALLING };

    uint8_t  mPin:6;
    uint8_t  mOn:1;
    bool     mBlink:1;
    uint8_t  mState;
    uint16_t mRiseTime;
    uint16_t mFallTime;
    uint16_t mOnTime;
    uint16_t mPeriod;
    uint32_t mNextEventDate;

    LightDimmer *mNext;
    static LightDimmer *sLightList;

    void updateState();

  public:
    LightDimmer(const uint8_t inPin, const uint8_t inOn);
    void begin();
    void setFadingTime(const uint16_t inFallTime);
    void setBrighteningTime(const uint16_t inRiseTime);
    void setOnTime(const uint16_t inOnTime);
    void setPeriod(const uint16_t inPeriod);
    void on();
    void off();
    void startBlink();
    void stopBlink();
    bool isOn()          { return (mState == LD_ON); }
    bool isOff()         { return (mState == LD_OFF); }
    bool isFading()      { return (mState == LD_FALLING); }
    bool isBrightening() { return (mState == LD_RISING); }

    static void update();
};

#endif
