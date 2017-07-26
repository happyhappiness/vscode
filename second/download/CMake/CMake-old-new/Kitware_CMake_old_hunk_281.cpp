#if defined(KWSYS_TERMINAL_SUPPORT_CONSOLE)
  CONSOLE_SCREEN_BUFFER_INFO hOutInfo;
  HANDLE hOut = kwsysTerminalGetStreamHandle(stream);
  if(GetConsoleScreenBufferInfo(hOut, &hOutInfo))
    {
    pipeIsConsole = 1;
    kwsysTerminalSetConsoleColor(hOut, &hOutInfo, stream, color);
    }
#endif
  if(!pipeIsConsole && kwsysTerminalStreamIsVT100(stream,
                                                  default_vt100, default_tty))
    {
    pipeIsVT100 = 1;
    kwsysTerminalSetVT100Color(stream, color);
    }

  /* Format the text into the stream.  */
  {
  va_list var_args;
  va_start(var_args, format);
  vfprintf(stream, format, var_args);
  va_end(var_args);
  }

  /* Restore the normal color state for the stream.  */
#if defined(KWSYS_TERMINAL_SUPPORT_CONSOLE)
  if(pipeIsConsole)
    {
    kwsysTerminalSetConsoleColor(hOut, &hOutInfo, stream,
                                 kwsysTerminal_Color_Normal);
    }
#endif
  if(pipeIsVT100)
    {
    kwsysTerminalSetVT100Color(stream, kwsysTerminal_Color_Normal);
    }
}

/*--------------------------------------------------------------------------*/
