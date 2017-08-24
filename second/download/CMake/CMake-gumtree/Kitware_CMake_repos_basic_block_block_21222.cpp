(!(ansi_parser_state & ANSI_IGNORE)) {
          if (utf8_codepoint >= '0' && utf8_codepoint <= '9') {
            /* Parsing a numerical argument */

            if (!(ansi_parser_state & ANSI_IN_ARG)) {
              /* We were not currently parsing a number */

              /* Check for too many arguments */
              if (handle->tty.wr.ansi_csi_argc >= ARRAY_SIZE(handle->tty.wr.ansi_csi_argv)) {
                ansi_parser_state |= ANSI_IGNORE;
                continue;
              }

              ansi_parser_state |= ANSI_IN_ARG;
              handle->tty.wr.ansi_csi_argc++;
              handle->tty.wr.ansi_csi_argv[handle->tty.wr.ansi_csi_argc - 1] =
                  (unsigned short) utf8_codepoint - '0';
              continue;
            } else {
              /* We were already parsing a number. Parse next digit. */
              uint32_t value = 10 *
                  handle->tty.wr.ansi_csi_argv[handle->tty.wr.ansi_csi_argc - 1];

              /* Check for overflow. */
              if (value > UINT16_MAX) {
                ansi_parser_state |= ANSI_IGNORE;
                continue;
              }

               handle->tty.wr.ansi_csi_argv[handle->tty.wr.ansi_csi_argc - 1] =
                   (unsigned short) value + (utf8_codepoint - '0');
               continue;
            }

          } else if (utf8_codepoint == ';') {
            /* Denotes the end of an argument. */
            if (ansi_parser_state & ANSI_IN_ARG) {
              ansi_parser_state &= ~ANSI_IN_ARG;
              continue;

            } else {
              /* If ANSI_IN_ARG is not set, add another argument and */
              /* default it to 0. */
              /* Check for too many arguments */
              if (handle->tty.wr.ansi_csi_argc >= ARRAY_SIZE(handle->tty.wr.ansi_csi_argv)) {
                ansi_parser_state |= ANSI_IGNORE;
                continue;
              }

              handle->tty.wr.ansi_csi_argc++;
              handle->tty.wr.ansi_csi_argv[handle->tty.wr.ansi_csi_argc - 1] = 0;
              continue;
            }

          } else if (utf8_codepoint == '?' && !(ansi_parser_state & ANSI_IN_ARG) &&
                     handle->tty.wr.ansi_csi_argc == 0) {
            /* Ignores '?' if it is the first character after CSI[ */
            /* This is an extension character from the VT100 codeset */
            /* that is supported and used by most ANSI terminals today. */
            continue;

          } else if (utf8_codepoint >= '@' && utf8_codepoint <= '~' &&
                     (handle->tty.wr.ansi_csi_argc > 0 || utf8_codepoint != '[')) {
            int x, y, d;

            /* Command byte */
            switch (utf8_codepoint) {
              case 'A':
                /* cursor up */
                FLUSH_TEXT();
                y = -(handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1);
                uv_tty_move_caret(handle, 0, 1, y, 1, error);
                break;

              case 'B':
                /* cursor down */
                FLUSH_TEXT();
                y = handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1;
                uv_tty_move_caret(handle, 0, 1, y, 1, error);
                break;

              case 'C':
                /* cursor forward */
                FLUSH_TEXT();
                x = handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1;
                uv_tty_move_caret(handle, x, 1, 0, 1, error);
                break;

              case 'D':
                /* cursor back */
                FLUSH_TEXT();
                x = -(handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1);
                uv_tty_move_caret(handle, x, 1, 0, 1, error);
                break;

              case 'E':
                /* cursor next line */
                FLUSH_TEXT();
                y = handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1;
                uv_tty_move_caret(handle, 0, 0, y, 1, error);
                break;

              case 'F':
                /* cursor previous line */
                FLUSH_TEXT();
                y = -(handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 1);
                uv_tty_move_caret(handle, 0, 0, y, 1, error);
                break;

              case 'G':
                /* cursor horizontal move absolute */
                FLUSH_TEXT();
                x = (handle->tty.wr.ansi_csi_argc >= 1 && handle->tty.wr.ansi_csi_argv[0])
                  ? handle->tty.wr.ansi_csi_argv[0] - 1 : 0;
                uv_tty_move_caret(handle, x, 0, 0, 1, error);
                break;

              case 'H':
              case 'f':
                /* cursor move absolute */
                FLUSH_TEXT();
                y = (handle->tty.wr.ansi_csi_argc >= 1 && handle->tty.wr.ansi_csi_argv[0])
                  ? handle->tty.wr.ansi_csi_argv[0] - 1 : 0;
                x = (handle->tty.wr.ansi_csi_argc >= 2 && handle->tty.wr.ansi_csi_argv[1])
                  ? handle->tty.wr.ansi_csi_argv[1] - 1 : 0;
                uv_tty_move_caret(handle, x, 0, y, 0, error);
                break;

              case 'J':
                /* Erase screen */
                FLUSH_TEXT();
                d = handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 0;
                if (d >= 0 && d <= 2) {
                  uv_tty_clear(handle, d, 1, error);
                }
                break;

              case 'K':
                /* Erase line */
                FLUSH_TEXT();
                d = handle->tty.wr.ansi_csi_argc ? handle->tty.wr.ansi_csi_argv[0] : 0;
                if (d >= 0 && d <= 2) {
                  uv_tty_clear(handle, d, 0, error);
                }
                break;

              case 'm':
                /* Set style */
                FLUSH_TEXT();
                uv_tty_set_style(handle, error);
                break;

              case 's':
                /* Save the cursor position. */
                FLUSH_TEXT();
                uv_tty_save_state(handle, 0, error);
                break;

              case 'u':
                /* Restore the cursor position */
                FLUSH_TEXT();
                uv_tty_restore_state(handle, 0, error);
                break;

              case 'l':
                /* Hide the cursor */
                if (handle->tty.wr.ansi_csi_argc == 1 &&
                    handle->tty.wr.ansi_csi_argv[0] == 25) {
                  FLUSH_TEXT();
                  uv_tty_set_cursor_visibility(handle, 0, error);
                }
                break;

              case 'h':
                /* Show the cursor */
                if (handle->tty.wr.ansi_csi_argc == 1 &&
                    handle->tty.wr.ansi_csi_argv[0] == 25) {
                  FLUSH_TEXT();
                  uv_tty_set_cursor_visibility(handle, 1, error);
                }
                break;
            }

            /* Sequence ended - go back to normal state. */
            ansi_parser_state = ANSI_NORMAL;
            continue;

          } else {
            /* We don't support commands that use private mode characters or */
            /* intermediaries. Ignore the rest of the sequence. */
            ansi_parser_state |= ANSI_IGNORE;
            continue;
          }
        } else {
          /* We're ignoring this command. Stop only on command character. */
          if (utf8_codepoint >= '@' && utf8_codepoint <= '~') {
            ansi_parser_state = ANSI_NORMAL;
          }
          continue;
        }