(ansi_parser_state == ANSI_ESCAPE_SEEN) {
        switch (utf8_codepoint) {
          case '[':
            ansi_parser_state = ANSI_CSI;
            handle->tty.wr.ansi_csi_argc = 0;
            continue;

          case '^':
          case '_':
          case 'P':
          case ']':
            /* Not supported, but we'll have to parse until we see a stop */
            /* code, e.g. ESC \ or BEL. */
            ansi_parser_state = ANSI_ST_CONTROL;
            continue;

          case '\033':
            /* Ignore double escape. */
            continue;

          case 'c':
            /* Full console reset. */
            FLUSH_TEXT();
            uv_tty_reset(handle, error);
            ansi_parser_state = ANSI_NORMAL;
            continue;

          case '7':
            /* Save the cursor position and text attributes. */
            FLUSH_TEXT();
            uv_tty_save_state(handle, 1, error);
            ansi_parser_state = ANSI_NORMAL;
            continue;

           case '8':
            /* Restore the cursor position and text attributes */
            FLUSH_TEXT();
            uv_tty_restore_state(handle, 1, error);
            ansi_parser_state = ANSI_NORMAL;
            continue;

          default:
            if (utf8_codepoint >= '@' && utf8_codepoint <= '_') {
              /* Single-char control. */
              ansi_parser_state = ANSI_NORMAL;
              continue;
            } else {
              /* Invalid - proceed as normal, */
              ansi_parser_state = ANSI_NORMAL;
            }
        }

      }