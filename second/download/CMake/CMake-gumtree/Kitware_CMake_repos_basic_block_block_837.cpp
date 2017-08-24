(c = in; *c; ++c) {
    /* Check whether this character needs quotes.  */
    if (strchr(" \t?'#&<>|^", *c)) {
      info.quote = 1;
    }

    /* On Windows only backslashes and double-quotes need escaping.  */
    if (*c == '\\') {
      /* Found a backslash.  It may need to be escaped later.  */
      ++windows_backslashes;
    } else if (*c == '"') {
      /* Found a double-quote.  We need to escape it and all
         immediately preceding backslashes.  */
      info.size += windows_backslashes + 1;
      windows_backslashes = 0;
    } else {
      /* Found another character.  This eliminates the possibility
         that any immediately preceding backslashes will be
         escaped.  */
      windows_backslashes = 0;
    }
  }