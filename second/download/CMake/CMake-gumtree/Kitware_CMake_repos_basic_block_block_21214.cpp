{
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