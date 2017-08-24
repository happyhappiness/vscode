(active_screen_buffer != INVALID_HANDLE_VALUE) {
        pos = uv__saved_screen_state.dwCursorPosition;

        /* If the cursor was at the bottom line of the screen buffer, the
           VK_RETURN would have caused the buffer contents to scroll up by one
           line. The right position to reset the cursor to is therefore one line
           higher */
        if (pos.Y == uv__saved_screen_state.dwSize.Y - 1)
          pos.Y--;

        SetConsoleCursorPosition(active_screen_buffer, pos);
        CloseHandle(active_screen_buffer);
      }