(handle->tty.wr.ansi_csi_argc >= ARRAY_SIZE(handle->tty.wr.ansi_csi_argv)) {
                ansi_parser_state |= ANSI_IGNORE;
                continue;
              }