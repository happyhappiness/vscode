(*c == '"') {
      /* Found a double-quote.  Escape all immediately preceding
         backslashes.  */
      while (windows_backslashes > 0) {
        --windows_backslashes;
        *out++ = '\\';
      }

      /* Add the backslash to escape the double-quote.  */
      *out++ = '\\';
    }