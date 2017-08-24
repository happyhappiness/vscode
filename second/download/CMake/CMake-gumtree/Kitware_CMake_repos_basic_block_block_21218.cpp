{
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
            }