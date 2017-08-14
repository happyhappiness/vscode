static void kwsysTerminalSetVT100Color(FILE* stream, int color)
{
  if (color == kwsysTerminal_Color_Normal) {
    fprintf(stream, KWSYS_TERMINAL_VT100_NORMAL);
    return;
  }

  switch (color & kwsysTerminal_Color_ForegroundMask) {
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
  switch (color & kwsysTerminal_Color_BackgroundMask) {
    case kwsysTerminal_Color_BackgroundBlack:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_BLACK);
      break;
    case kwsysTerminal_Color_BackgroundRed:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_RED);
      break;
    case kwsysTerminal_Color_BackgroundGreen:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_GREEN);
      break;
    case kwsysTerminal_Color_BackgroundYellow:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_YELLOW);
      break;
    case kwsysTerminal_Color_BackgroundBlue:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_BLUE);
      break;
    case kwsysTerminal_Color_BackgroundMagenta:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_MAGENTA);
      break;
    case kwsysTerminal_Color_BackgroundCyan:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_CYAN);
      break;
    case kwsysTerminal_Color_BackgroundWhite:
      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_WHITE);
      break;
  }
  if (color & kwsysTerminal_Color_ForegroundBold) {
    fprintf(stream, KWSYS_TERMINAL_VT100_BOLD);
  }
}