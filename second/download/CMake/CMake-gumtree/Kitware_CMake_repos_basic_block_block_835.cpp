(*c == '"') {
      /* Found a double-quote.  We need to escape it and all
         immediately preceding backslashes.  */
      info.size += windows_backslashes + 1;
      windows_backslashes = 0;
    }