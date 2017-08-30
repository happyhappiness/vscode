    case kwsysTerminal_Color_ForegroundWhite:

      fprintf(stream, KWSYS_TERMINAL_VT100_FOREGROUND_WHITE);

      break;

    }

  switch(color & kwsysTerminal_Color_BackgroundMask)

    {

    case kwsysTerminal_Color_BackgroundBlack:

      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_BLACK);

      break;

