(n > 0) {
      ff.LastCharWasNewline = buffer[n - 1] == '\n';
    } else if (!ff.LastCharWasNewline) {
      // The file ended without a newline.  Inject one so
      // that the file always ends in an end-of-statement.
      buffer[0] = '\n';
      n = 1;
      ff.LastCharWasNewline = true;
    }