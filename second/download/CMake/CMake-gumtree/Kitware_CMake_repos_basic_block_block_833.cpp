{
    /* Surrounding quotes are needed.  Allocate space for them.  */
    info.size += 2;

    /* We must escape all ending backslashes when quoting on windows.  */
    info.size += windows_backslashes;
  }