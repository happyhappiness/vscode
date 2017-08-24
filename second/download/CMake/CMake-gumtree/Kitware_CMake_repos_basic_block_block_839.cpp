{
    /* Add enough backslashes to escape any trailing ones.  */
    while (windows_backslashes > 0) {
      --windows_backslashes;
      *out++ = '\\';
    }

    /* Add the closing quote for this argument.  */
    *out++ = '"';
  }