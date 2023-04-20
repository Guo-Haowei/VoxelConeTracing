#include "Input.h"

#include "Core/Check.h"

Input Input::gInput;

Input::Input()
{
#if USING(ENABLE_CHECK)
    static int sCounter = 0;
    checkfmt(++sCounter == 1, "Input::Input() should be called only once");
#endif

    mKeys.fill(false);
    mPrevKeys.fill(false);
    mButtons.fill(false);
    mPrevButtons.fill(false);
}

void Input::BeginFrame()
{
    // called after glfwPollEvent, before everything else
}

void Input::EndFrame()
{
    gInput.mPrevKeys = gInput.mKeys;
    gInput.mPrevButtons = gInput.mButtons;
    gInput.mPrevCursor = gInput.mCursor;

    gInput.mWheel = Point(0);
}

template<size_t N>
static inline bool InputIsDown(const std::array<bool, N>& arr, int index)
{
    checkrange(index, 0, N);
    return arr[index];
}

template<size_t N>
static inline bool InputChange(const std::array<bool, N>& current, const std::array<bool, N>& prev, int index)
{
    checkrange(index, 0, N);
    return current[index] == true && prev[index] == false;
}

bool Input::IsButtonDown(EMouseButton key)
{
    return InputIsDown(gInput.mButtons, underlying(key));
}

bool Input::IsButtonPressed(EMouseButton key)
{
    return InputChange(gInput.mButtons, gInput.mPrevButtons, underlying(key));
}

bool Input::IsButtonReleased(EMouseButton key)
{
    return InputChange(gInput.mPrevButtons, gInput.mButtons, underlying(key));
}

bool Input::IsKeyDown(EKeyCode key)
{
    return InputIsDown(gInput.mKeys, underlying(key));
}

bool Input::IsKeyPressed(EKeyCode key)
{
    return InputChange(gInput.mKeys, gInput.mPrevKeys, underlying(key));
}

bool Input::IsKeyReleased(EKeyCode key)
{
    return InputChange(gInput.mPrevKeys, gInput.mKeys, underlying(key));
}

Point Input::MouseMove()
{
    Point point;
    point = gInput.mCursor - gInput.mPrevCursor;
    return point;
}

const Point& Input::Wheel()
{
    return gInput.mWheel;
}

void Input::SetButton(int button, bool pressed)
{
    checkrange(button, 0, EMouseButton::COUNT);
    mButtons[button] = pressed;
}

void Input::SetKey(int key, bool pressed)
{
    checkrange(key, 0, EKeyCode::COUNT);
    mKeys[key] = pressed;
}

void Input::SetCursor(float x, float y)
{
    mCursor.x = x;
    mCursor.y = y;
}

void Input::SetWheel(float x, float y)
{
    mWheel.x = x;
    mWheel.y = y;
}