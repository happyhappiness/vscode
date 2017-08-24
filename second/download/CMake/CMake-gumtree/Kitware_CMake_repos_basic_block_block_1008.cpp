(; k != bracket_last; ++k) {
          // Backslashes must be escaped.
          if (*k == '\\') {
            regex += "\\";
          }

          // Store this character.
          regex += *k;
        }