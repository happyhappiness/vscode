(handle->tty.rd.last_key_len == 0) {
      /* Read the next input record */
      if (!ReadConsoleInputW(handle->handle,
                             &handle->tty.rd.last_input_record,
                             1,
                             &records_read)) {
        handle->flags &= ~UV_HANDLE_READING;
        DECREASE_ACTIVE_COUNT(loop, handle);
        handle->read_cb((uv_stream_t*) handle,
                        uv_translate_sys_error(GetLastError()),
                        &buf);
        goto out;
      }
      records_left--;

      /* If the window was resized, recompute the virtual window size. This */
      /* will trigger a SIGWINCH signal if the window size changed in an */
      /* way that matters to libuv. */
      if (handle->tty.rd.last_input_record.EventType == WINDOW_BUFFER_SIZE_EVENT) {
        CONSOLE_SCREEN_BUFFER_INFO info;

        uv_sem_wait(&uv_tty_output_lock);

        if (uv_tty_output_handle != INVALID_HANDLE_VALUE &&
            GetConsoleScreenBufferInfo(uv_tty_output_handle, &info)) {
          uv_tty_update_virtual_window(&info);
        }

        uv_sem_post(&uv_tty_output_lock);

        continue;
      }

      /* Ignore other events that are not key or resize events. */
      if (handle->tty.rd.last_input_record.EventType != KEY_EVENT) {
        continue;
      }

      /* Ignore keyup events, unless the left alt key was held and a valid */
      /* unicode character was emitted. */
      if (!KEV.bKeyDown && !(((KEV.dwControlKeyState & LEFT_ALT_PRESSED) ||
          KEV.wVirtualKeyCode==VK_MENU) && KEV.uChar.UnicodeChar != 0)) {
        continue;
      }

      /* Ignore keypresses to numpad number keys if the left alt is held */
      /* because the user is composing a character, or windows simulating */
      /* this. */
      if ((KEV.dwControlKeyState & LEFT_ALT_PRESSED) &&
          !(KEV.dwControlKeyState & ENHANCED_KEY) &&
          (KEV.wVirtualKeyCode == VK_INSERT ||
          KEV.wVirtualKeyCode == VK_END ||
          KEV.wVirtualKeyCode == VK_DOWN ||
          KEV.wVirtualKeyCode == VK_NEXT ||
          KEV.wVirtualKeyCode == VK_LEFT ||
          KEV.wVirtualKeyCode == VK_CLEAR ||
          KEV.wVirtualKeyCode == VK_RIGHT ||
          KEV.wVirtualKeyCode == VK_HOME ||
          KEV.wVirtualKeyCode == VK_UP ||
          KEV.wVirtualKeyCode == VK_PRIOR ||
          KEV.wVirtualKeyCode == VK_NUMPAD0 ||
          KEV.wVirtualKeyCode == VK_NUMPAD1 ||
          KEV.wVirtualKeyCode == VK_NUMPAD2 ||
          KEV.wVirtualKeyCode == VK_NUMPAD3 ||
          KEV.wVirtualKeyCode == VK_NUMPAD4 ||
          KEV.wVirtualKeyCode == VK_NUMPAD5 ||
          KEV.wVirtualKeyCode == VK_NUMPAD6 ||
          KEV.wVirtualKeyCode == VK_NUMPAD7 ||
          KEV.wVirtualKeyCode == VK_NUMPAD8 ||
          KEV.wVirtualKeyCode == VK_NUMPAD9)) {
        continue;
      }

      if (KEV.uChar.UnicodeChar != 0) {
        int prefix_len, char_len;

        /* Character key pressed */
        if (KEV.uChar.UnicodeChar >= 0xD800 &&
            KEV.uChar.UnicodeChar < 0xDC00) {
          /* UTF-16 high surrogate */
          handle->tty.rd.last_utf16_high_surrogate = KEV.uChar.UnicodeChar;
          continue;
        }

        /* Prefix with \u033 if alt was held, but alt was not used as part */
        /* a compose sequence. */
        if ((KEV.dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            && !(KEV.dwControlKeyState & (LEFT_CTRL_PRESSED |
            RIGHT_CTRL_PRESSED)) && KEV.bKeyDown) {
          handle->tty.rd.last_key[0] = '\033';
          prefix_len = 1;
        } else {
          prefix_len = 0;
        }

        if (KEV.uChar.UnicodeChar >= 0xDC00 &&
            KEV.uChar.UnicodeChar < 0xE000) {
          /* UTF-16 surrogate pair */
          WCHAR utf16_buffer[2] = { handle->tty.rd.last_utf16_high_surrogate,
                                    KEV.uChar.UnicodeChar};
          char_len = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         utf16_buffer,
                                         2,
                                         &handle->tty.rd.last_key[prefix_len],
                                         sizeof handle->tty.rd.last_key,
                                         NULL,
                                         NULL);
        } else {
          /* Single UTF-16 character */
          char_len = WideCharToMultiByte(CP_UTF8,
                                         0,
                                         &KEV.uChar.UnicodeChar,
                                         1,
                                         &handle->tty.rd.last_key[prefix_len],
                                         sizeof handle->tty.rd.last_key,
                                         NULL,
                                         NULL);
        }

        /* Whatever happened, the last character wasn't a high surrogate. */
        handle->tty.rd.last_utf16_high_surrogate = 0;

        /* If the utf16 character(s) couldn't be converted something must */
        /* be wrong. */
        if (!char_len) {
          handle->flags &= ~UV_HANDLE_READING;
          DECREASE_ACTIVE_COUNT(loop, handle);
          handle->read_cb((uv_stream_t*) handle,
                          uv_translate_sys_error(GetLastError()),
                          &buf);
          goto out;
        }

        handle->tty.rd.last_key_len = (unsigned char) (prefix_len + char_len);
        handle->tty.rd.last_key_offset = 0;
        continue;

      } else {
        /* Function key pressed */
        const char* vt100;
        size_t prefix_len, vt100_len;

        vt100 = get_vt100_fn_key(KEV.wVirtualKeyCode,
                                  !!(KEV.dwControlKeyState & SHIFT_PRESSED),
                                  !!(KEV.dwControlKeyState & (
                                    LEFT_CTRL_PRESSED |
                                    RIGHT_CTRL_PRESSED)),
                                  &vt100_len);

        /* If we were unable to map to a vt100 sequence, just ignore. */
        if (!vt100) {
          continue;
        }

        /* Prefix with \x033 when the alt key was held. */
        if (KEV.dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED)) {
          handle->tty.rd.last_key[0] = '\033';
          prefix_len = 1;
        } else {
          prefix_len = 0;
        }

        /* Copy the vt100 sequence to the handle buffer. */
        assert(prefix_len + vt100_len < sizeof handle->tty.rd.last_key);
        memcpy(&handle->tty.rd.last_key[prefix_len], vt100, vt100_len);

        handle->tty.rd.last_key_len = (unsigned char) (prefix_len + vt100_len);
        handle->tty.rd.last_key_offset = 0;
        continue;
      }
    } else {
      /* Copy any bytes left from the last keypress to the user buffer. */
      if (handle->tty.rd.last_key_offset < handle->tty.rd.last_key_len) {
        /* Allocate a buffer if needed */
        if (buf_used == 0) {
          buf = uv_buf_init(NULL, 0);
          handle->alloc_cb((uv_handle_t*) handle, 1024, &buf);
          if (buf.base == NULL || buf.len == 0) {
            handle->read_cb((uv_stream_t*) handle, UV_ENOBUFS, &buf);
            goto out;
          }
          assert(buf.base != NULL);
        }

        buf.base[buf_used++] = handle->tty.rd.last_key[handle->tty.rd.last_key_offset++];

        /* If the buffer is full, emit it */
        if ((size_t) buf_used == buf.len) {
          handle->read_cb((uv_stream_t*) handle, buf_used, &buf);
          buf = uv_null_buf_;
          buf_used = 0;
        }

        continue;
      }

      /* Apply dwRepeat from the last input record. */
      if (--KEV.wRepeatCount > 0) {
        handle->tty.rd.last_key_offset = 0;
        continue;
      }

      handle->tty.rd.last_key_len = 0;
      continue;
    }