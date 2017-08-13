{
    case kwsysTerminal_Color_Normal:
      fprintf(stream, KWSYS_TERMINAL_VT100_NORMAL);
      break;
    case kwsysTerminal_Color_ForegroundBlack:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_BLACK);
      break;
    case kwsysTerminal_Color_ForegroundRed:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_RED);
      break;
    case kwsysTerminal_Color_ForegroundGreen:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_GREEN);
      break;
    case kwsysTerminal_Color_ForegroundYellow:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_YELLOW);
      break;
    case kwsysTerminal_Color_ForegroundBlue:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_BLUE);
      break;
    case kwsysTerminal_Color_ForegroundMagenta:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_MAGENTA);
      break;
    case kwsysTerminal_Color_ForegroundCyan:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_CYAN);
      break;
    case kwsysTerminal_Color_ForegroundWhite:
      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_WHITE);
      break;
  }