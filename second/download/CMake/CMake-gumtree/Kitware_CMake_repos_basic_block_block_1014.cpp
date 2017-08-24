{
      // A single character matches itself.
      int ch = c;
      if (!(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') ||
            ('0' <= ch && ch <= '9'))) {
        // Escape the non-alphanumeric character.
        regex += "\\";
      }
#if defined(KWSYS_GLOB_CASE_INDEPENDENT)
      else {
        // On case-insensitive systems file names are converted to lower
        // case before matching.
        if (!preserve_case) {
          ch = tolower(ch);
        }
      }
#endif
      (void)preserve_case;
      // Store the character.
      regex.append(1, static_cast<char>(ch));
    }