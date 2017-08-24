(*c == '\\') {
      /* Found a backslash.  It may need to be escaped later.  */
      ++windows_backslashes;
    } else if (*c == '"') {
      /* Found a double-quote.  Escape all immediately preceding
         backslashes.  */
      while (windows_backslashes > 0) {
        --windows_backslashes;
        *out++ = '\\';
      }

      /* Add the backslash to escape the double-quote.  */
      *out++ = '\\';
    } else {
      /* We encountered a normal character.  This eliminates any
         escaping needed for preceding backslashes.  */
      windows_backslashes = 0;
    }