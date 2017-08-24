(!(ansi_parser_state & ANSI_BACKSLASH_SEEN)) {
            if (utf8_codepoint == '"') {
              ansi_parser_state &= ~ANSI_IN_STRING;
            } else if (utf8_codepoint == '\\') {
              ansi_parser_state |= ANSI_BACKSLASH_SEEN;
            }
          } else {
            ansi_parser_state &= ~ANSI_BACKSLASH_SEEN;
          }