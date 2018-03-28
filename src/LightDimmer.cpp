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

#include <LightDimmer.h>

LightDimmer *LightDimmer::sLightList = NULL;

LightDimmer::LightDimmer(const uint8_t inPin, const uint8_t inOn)
  : mPin(inPin),
    mOn(inOn),
    mBlink(false),
    mState(LD_OFF),
    mValue(0),
    mRiseTime(250),
    mFallTime(250),
    mOnTime(200),
    mPeriod(900),
    mNextEventDate(0)
{
  mNext = sLightList;
  sLightList = this;
}

void LightDimmer::begin()
{
  pinMode(mPin, OUTPUT);
  /* At start, le LED is switched off */
  digitalWrite(mPin, !mOn);
}

void LightDimmer::setFadingTime(const uint16_t inFallTime)
{
  mFallTime = inFallTime;
}

void LightDimmer::setBrighteningTime(const uint16_t inRiseTime)
{
  mRiseTime = inRiseTime;
}

void LightDimmer::on()
{
  switch (mState)
  {
    case LD_OFF:
      mNextEventDate = millis() + mRiseTime;
      mState = LD_RISING;
      break;
    case LD_FALLING:
      uint32_t remainingTime = mNextEventDate - millis();
      mNextEventDate = millis() + (uint32_t)mRiseTime * remainingTime / (uint32_t)mFallTime;
      mState = LD_RISING;
      break;
  }
  mBlink = false;
}

void LightDimmer::off()
{
  switch (mState)
  {
    case LD_ON:
      mNextEventDate = millis() + mFallTime;
      mState = LD_FALLING;
      break;
    case LD_RISING:
      uint32_t remainingTime = mNextEventDate - millis();
      mNextEventDate = millis() + (uint32_t)mFallTime * remainingTime / (uint32_t)mRiseTime;
      mState = LD_FALLING;
      break;
  }
  mBlink = false;
}

void LightDimmer::startBlink()
{
  if (mPeriod >= mRiseTime + mOnTime + mFallTime) {
    mBlink = true;
  }
}

void LightDimmer::stopBlink()
{
  mBlink = false;
}

void LightDimmer::updateState()
{
  uint32_t currentDate = millis();
  switch (mState) {
    case LD_OFF:
      if (mBlink) {
        if (currentDate >= mNextEventDate) {
          mNextEventDate = millis() + mRiseTime;
          mState = LD_RISING;
        }
      }
      break;
    case LD_RISING:
      if (currentDate < mNextEventDate) {
        uint8_t value = 255 * (currentDate - (mNextEventDate - mRiseTime)) / mRiseTime;
        analogWrite(mPin, mOn ? value : 255 - value);
      }
      else {
        digitalWrite(mPin, mOn);
        mNextEventDate = currentDate + mPeriod - mOnTime - mRiseTime -mFallTime;
        mState = LD_ON;
      }
      break;
    case LD_ON:
      if (mBlink) {
        if (currentDate >= mNextEventDate) {
          mNextEventDate = currentDate + mFallTime;
          mState = LD_FALLING;
        }
      }
      break;
    case LD_FALLING:
      if (currentDate < mNextEventDate) {
        uint8_t value = 255 * (currentDate - (mNextEventDate - mFallTime)) / mFallTime;
        analogWrite(mPin, mOn ? 255 - value : value);
      }
      else {
        digitalWrite(mPin, !mOn);
        mState = LD_OFF;
        mNextEventDate = currentDate + mPeriod - mOnTime - mRiseTime - mFallTime;
      }
      break;
  }
}

static void LightDimmer::update()
{
  LightDimmer *ld = sLightList;
  while (ld != NULL) {
    ld->updateState();
    ld = ld->mNext;
  }
}
