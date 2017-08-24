(!(ansi_parser_state & ANSI_IN_ARG)) {
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