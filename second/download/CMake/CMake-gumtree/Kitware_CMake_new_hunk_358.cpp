    case kwsysTerminal_Color_BackgroundWhite:

      fprintf(stream, KWSYS_TERMINAL_VT100_BACKGROUND_WHITE);

      break;

  }

  if (color & kwsysTerminal_Color_ForegroundBold) {

    fprintf(stream, KWSYS_TERMINAL_VT100_BOLD);

  }

}



/*--------------------------------------------------------------------------*/

#if defined(KWSYS_TERMINAL_SUPPORT_CONSOLE)



#define KWSYS_TERMINAL_MASK_FOREGROUND                                        \

  (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

#define KWSYS_TERMINAL_MASK_BACKGROUND                                        \

  (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)



/* Get the Windows handle for a FILE stream.  */

