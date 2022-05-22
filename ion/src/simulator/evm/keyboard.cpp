#include <ion/keyboard.h>
#include "platform.h"
#include "main.h"

#include "keyboard.h"
#include "sys_llapi.h"
#include <stdio.h>
extern "C"
{
  extern uint32_t key;
  extern bool key_press;
}
void IonSimulatorKeyboardKeyDown(int keyNumber)
{
}

void IonSimulatorKeyboardKeyUp(int keyNumber)
{
}

namespace Ion
{
  namespace Keyboard
  {

    State scan()
    {
      Simulator::Main::refresh();
      // printf("Scan key.\n");

      State state;

      key = ll_vm_check_key();
      key_press = key >> 16;
      key = key & 0xFFFF;

      if(key_press)
      {
        switch (key)
        {
        case KEY_RIGHT:
          state.setKey(Key::Right);break;
        case KEY_LEFT:
          state.setKey(Key::Left);break;
        case KEY_UP:
          state.setKey(Key::Up);break;
        case KEY_DOWN:
          state.setKey(Key::Down);break;
        case KEY_ENTER:
          state.setKey(Key::EXE);break;
        case KEY_SIN:
          state.setKey(Key::Sine);break;
        case KEY_0:
          state.setKey(Key::Zero);break;
        case KEY_1:
          state.setKey(Key::One);break;
        case KEY_2:
          state.setKey(Key::Two);break;
        case KEY_3:
          state.setKey(Key::Three);break;
        case KEY_4:
          state.setKey(Key::Four);break;
        case KEY_5:
          state.setKey(Key::Five);break;
        case KEY_6:
          state.setKey(Key::Six);break;
        case KEY_7:
          state.setKey(Key::Seven);break;
        case KEY_8:
          state.setKey(Key::Eight);break;
        case KEY_9:
          state.setKey(Key::Nine);break;
        case KEY_HOME:
          state.setKey(Key::Home);break;
        case KEY_BACKSPACE:
          state.setKey(Key::Backspace);break;
        case KEY_F1:
          state.setKey(Key::Back);break;
        case KEY_F6:
          state.setKey(Key::Ans);break;
        case KEY_DOT:
          state.setKey(Key::Dot);break;
        case KEY_PLUS:
          state.setKey(Key::Plus);break;
        case KEY_MULTIPLICATION:
          state.setKey(Key::Multiplication);break;
        case KEY_DIVISION:
          state.setKey(Key::Division);break;
        case KEY_SUBTRACTION:
          state.setKey(Key::Minus);break;
        case KEY_VARS:
          state.setKey(Key::Var);break;
        case KEY_MATH:
          state.setKey(Key::Toolbox);break;
        case KEY_TAN:
          state.setKey(Key::Tangent);break;
        case KEY_COS:
          state.setKey(Key::Cosine);break;
        case KEY_COMMA:
          state.setKey(Key::Comma);break;
        case KEY_LEFTBRACKET:
          state.setKey(Key::LeftParenthesis);break;
        case KEY_RIGHTBRACET:
          state.setKey(Key::RightParenthesis);break;
        case KEY_LN:
          state.setKey(Key::Ln);break;
        case KEY_LOG:
          state.setKey(Key::Log);break;
        case KEY_SHIFT:
          state.setKey(Key::Shift);break;
        case KEY_ALPHA:
          state.setKey(Key::Alpha);break;
        case KEY_XTPHIN:
          state.setKey(Key::XNT);break;
        default:
          break;
        }
      }
      

      return state;
    }

  }
}
