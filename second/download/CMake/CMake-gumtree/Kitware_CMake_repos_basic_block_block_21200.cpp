{
             /* String starting */
            ansi_parser_state |= ANSI_IN_STRING;
            ansi_parser_state &= ~ANSI_ESCAPE_SEEN;
            ansi_parser_state &= ~ANSI_BACKSLASH_SEEN;
          }