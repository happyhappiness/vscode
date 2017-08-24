{
    /* If we canceled the read by sending a VK_RETURN event, restore the
       screen state to undo the visual effect of the VK_RETURN */
    if (read_console_success && InterlockedOr(&uv__restore_screen_state, 0)) {
      HANDLE active_screen_buffer;
      active_screen_buffer = CreateFileA("conout$",
                                         GENERIC_READ | GENERIC_WRITE,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                                         NULL,
                                         OPEN_EXISTING,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL);
      if (active_screen_buffer != INVALID_HANDLE_VALUE) {
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
    }
    uv_sem_post(&uv_tty_output_lock);
  }