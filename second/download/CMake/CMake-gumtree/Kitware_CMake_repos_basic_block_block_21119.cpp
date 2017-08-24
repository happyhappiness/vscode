{
  HANDLE active_screen_buffer = INVALID_HANDLE_VALUE;
  INPUT_RECORD record;
  DWORD written;
  DWORD err = 0;
  LONG status;

  assert(!(handle->flags & UV_HANDLE_CANCELLATION_PENDING));

  /* Hold the output lock during the cancellation, to ensure that further
     writes don't interfere with the screen state. It will be the ReadConsole
     thread's responsibility to release the lock. */
  uv_sem_wait(&uv_tty_output_lock);
  status = InterlockedExchange(&uv__read_console_status, TRAP_REQUESTED);
  if (status != IN_PROGRESS) {
    /* Either we have managed to set a trap for the other thread before
       ReadConsole is called, or ReadConsole has returned because the user
       has pressed ENTER. In either case, there is nothing else to do. */
    uv_sem_post(&uv_tty_output_lock);
    return 0;
  }

  /* Save screen state before sending the VK_RETURN event */
  active_screen_buffer = CreateFileA("conout$",
                                     GENERIC_READ | GENERIC_WRITE,
                                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL);

  if (active_screen_buffer != INVALID_HANDLE_VALUE &&
      GetConsoleScreenBufferInfo(active_screen_buffer,
                                 &uv__saved_screen_state)) {
    InterlockedOr(&uv__restore_screen_state, 1);
  }

  /* Write enter key event to force the console wait to return. */
  record.EventType = KEY_EVENT;
  record.Event.KeyEvent.bKeyDown = TRUE;
  record.Event.KeyEvent.wRepeatCount = 1;
  record.Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
  record.Event.KeyEvent.wVirtualScanCode =
    MapVirtualKeyW(VK_RETURN, MAPVK_VK_TO_VSC);
  record.Event.KeyEvent.uChar.UnicodeChar = L'\r';
  record.Event.KeyEvent.dwControlKeyState = 0;
  if (!WriteConsoleInputW(handle->handle, &record, 1, &written))
    err = GetLastError();

  if (active_screen_buffer != INVALID_HANDLE_VALUE)
    CloseHandle(active_screen_buffer);

  return err;
}