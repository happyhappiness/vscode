(i = 0; i < nbufs; i++) {
    uv_buf_t buf = bufs[i];
    unsigned int j;

    if (uv__vterm_state == UV_SUPPORTED && buf.len > 0) {
      utf16_buf_used = MultiByteToWideChar(CP_UTF8,
                                           0,
                                           buf.base,
                                           buf.len,
                                           NULL,
                                           0);

      if (utf16_buf_used == 0) {
        *error = GetLastError();
        break;
      }

      max_len = (utf16_buf_used + 1) * sizeof(WCHAR);
      allocate = max_len > MAX_CONSOLE_CHAR;
      if (allocate)
        utf16_buffer = uv__malloc(max_len);
      if (!MultiByteToWideChar(CP_UTF8,
                               0,
                               buf.base,
                               buf.len,
                               utf16_buffer,
                               utf16_buf_used)) {
        if (allocate)
          uv__free(utf16_buffer);
        *error = GetLastError();
        break;
      }

      FLUSH_TEXT();

      continue;
    }

    for (j = 0; j < buf.len; j++) {
      unsigned char c = buf.base[j];

      /* Run the character through the utf8 decoder We happily accept non */
      /* shortest form encodings and invalid code points - there's no real */
      /* harm that can be done. */
      if (utf8_bytes_left == 0) {
        /* Read utf-8 start byte */
        DWORD first_zero_bit;
        unsigned char not_c = ~c;
#ifdef _MSC_VER /* msvc */
        if (_BitScanReverse(&first_zero_bit, not_c)) {
#else /* assume gcc */
        if (c != 0) {
          first_zero_bit = (sizeof(int) * 8) - 1 - __builtin_clz(not_c);
#endif
          if (first_zero_bit == 7) {
            /* Ascii - pass right through */
            utf8_codepoint = (unsigned int) c;

          } else if (first_zero_bit <= 5) {
            /* Multibyte sequence */
            utf8_codepoint = (0xff >> (8 - first_zero_bit)) & c;
            utf8_bytes_left = (char) (6 - first_zero_bit);

          } else {
            /* Invalid continuation */
            utf8_codepoint = UNICODE_REPLACEMENT_CHARACTER;
          }

        } else {
          /* 0xff -- invalid */
          utf8_codepoint = UNICODE_REPLACEMENT_CHARACTER;
        }

      } else if ((c & 0xc0) == 0x80) {
        /* Valid continuation of utf-8 multibyte sequence */
        utf8_bytes_left--;
        utf8_codepoint <<= 6;
        utf8_codepoint |= ((unsigned int) c & 0x3f);

      } else {
        /* Start byte where continuation was expected. */
        utf8_bytes_left = 0;
        utf8_codepoint = UNICODE_REPLACEMENT_CHARACTER;
        /* Patch buf offset so this character will be parsed again as a */
        /* start byte. */
        j--;
      }

      /* Maybe we need to parse more bytes to find a character. */
      if (utf8_bytes_left != 0) {
        continue;
      }

      /* Parse vt100/ansi escape codes */
      if (ansi_parser_state == ANSI_NORMAL) {
        switch (utf8_codepoint) {
          case '\033':
            ansi_parser_state = ANSI_ESCAPE_SEEN;
            continue;

          case 0233:
            ansi_parser_state = ANSI_CSI;
            handle->tty.wr.ansi_csi_argc = 0;
            continue;
        }

      } else if (ansi_parser_state == ANSI_ESCAPE_SEEN) {
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

      } else if (ansi_parser_state & ANSI_CSI) {
        if (!(ansi_parser_state & ANSI_IGNORE)) {
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

      } else if (ansi_parser_state & ANSI_ST_CONTROL) {
        /* Unsupported control code */
        /* Ignore everything until we see BEL or ESC \ */
        if (ansi_parser_state & ANSI_IN_STRING) {
          if (!(ansi_parser_state & ANSI_BACKSLASH_SEEN)) {
            if (utf8_codepoint == '"') {
              ansi_parser_state &= ~ANSI_IN_STRING;
            } else if (utf8_codepoint == '\\') {
              ansi_parser_state |= ANSI_BACKSLASH_SEEN;
            }
          } else {
            ansi_parser_state &= ~ANSI_BACKSLASH_SEEN;
          }
        } else {
          if (utf8_codepoint == '\007' || (utf8_codepoint == '\\' &&
              (ansi_parser_state & ANSI_ESCAPE_SEEN))) {
            /* End of sequence */
            ansi_parser_state = ANSI_NORMAL;
          } else if (utf8_codepoint == '\033') {
            /* Escape character */
            ansi_parser_state |= ANSI_ESCAPE_SEEN;
          } else if (utf8_codepoint == '"') {
             /* String starting */
            ansi_parser_state |= ANSI_IN_STRING;
            ansi_parser_state &= ~ANSI_ESCAPE_SEEN;
            ansi_parser_state &= ~ANSI_BACKSLASH_SEEN;
          } else {
            ansi_parser_state &= ~ANSI_ESCAPE_SEEN;
          }
        }
        continue;
      } else {
        /* Inconsistent state */
        abort();
      }

      /* We wouldn't mind emitting utf-16 surrogate pairs. Too bad, the */
      /* windows console doesn't really support UTF-16, so just emit the */
      /* replacement character. */
      if (utf8_codepoint > 0xffff) {
        utf8_codepoint = UNICODE_REPLACEMENT_CHARACTER;
      }

      if (utf8_codepoint == 0x0a || utf8_codepoint == 0x0d) {
        /* EOL conversion - emit \r\n when we see \n. */

        if (utf8_codepoint == 0x0a && previous_eol != 0x0d) {
          /* \n was not preceded by \r; print \r\n. */
          ENSURE_BUFFER_SPACE(2);
          utf16_buf[utf16_buf_used++] = L'\r';
          utf16_buf[utf16_buf_used++] = L'\n';
        } else if (utf8_codepoint == 0x0d && previous_eol == 0x0a) {
          /* \n was followed by \r; do not print the \r, since */
          /* the source was either \r\n\r (so the second \r is */
          /* redundant) or was \n\r (so the \n was processed */
          /* by the last case and an \r automatically inserted). */
        } else {
          /* \r without \n; print \r as-is. */
          ENSURE_BUFFER_SPACE(1);
          utf16_buf[utf16_buf_used++] = (WCHAR) utf8_codepoint;
        }

        previous_eol = (char) utf8_codepoint;

      } else if (utf8_codepoint <= 0xffff) {
        /* Encode character into utf-16 buffer. */
        ENSURE_BUFFER_SPACE(1);
        utf16_buf[utf16_buf_used++] = (WCHAR) utf8_codepoint;
        previous_eol = 0;
      }
    }
  }

  /* Flush remaining characters */
  FLUSH_TEXT();

  /* Copy cached values back to struct. */
  handle->tty.wr.utf8_bytes_left = utf8_bytes_left;
  handle->tty.wr.utf8_codepoint = utf8_codepoint;
  handle->tty.wr.previous_eol = previous_eol;
  handle->tty.wr.ansi_parser_state = ansi_parser_state;

  uv_sem_post(&uv_tty_output_lock);

  if (*error == STATUS_SUCCESS) {
    return 0;
  } else {
    return -1;
  }

#undef FLUSH_TEXT
}