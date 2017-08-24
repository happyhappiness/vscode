{
    case kwsysTerminal_Color_Normal:
      attributes |= hOutInfo->wAttributes & KWSYS_TERMINAL_MASK_FOREGROUND;
      break;
    case kwsysTerminal_Color_ForegroundBlack:
      attributes |= 0;
      break;
    case kwsysTerminal_Color_ForegroundRed:
      attributes |= FOREGROUND_RED;
      break;
    case kwsysTerminal_Color_ForegroundGreen:
      attributes |= FOREGROUND_GREEN;
      break;
    case kwsysTerminal_Color_ForegroundYellow:
      attributes |= FOREGROUND_RED | FOREGROUND_GREEN;
      break;
    case kwsysTerminal_Color_ForegroundBlue:
      attributes |= FOREGROUND_BLUE;
      break;
    case kwsysTerminal_Color_ForegroundMagenta:
      attributes |= FOREGROUND_RED | FOREGROUND_BLUE;
      break;
    case kwsysTerminal_Color_ForegroundCyan:
      attributes |= FOREGROUND_BLUE | FOREGROUND_GREEN;
      break;
    case kwsysTerminal_Color_ForegroundWhite:
      attributes |= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
      break;
  }