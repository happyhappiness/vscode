static DWORD WINAPI select_ws_wait_thread(LPVOID lpParameter)
{
  struct select_ws_wait_data *data;
  HANDLE handle, handles[2];
  INPUT_RECORD inputrecord;
  LARGE_INTEGER size, pos;
  DWORD type, length;

  /* retrieve handles from internal structure */
  data = (struct select_ws_wait_data *) lpParameter;
  if(data) {
    handle = data->handle;
    handles[0] = data->event;
    handles[1] = handle;
    free(data);
  }
  else
    return (DWORD)-1;

  /* retrieve the type of file to wait on */
  type = GetFileType(handle);
  switch(type) {
    case FILE_TYPE_DISK:
       /* The handle represents a file on disk, this means:
        * - WaitForMultipleObjectsEx will always be signalled for it.
        * - comparison of current position in file and total size of
        *   the file can be used to check if we reached the end yet.
        *
        * Approach: Loop till either the internal event is signalled
        *           or if the end of the file has already been reached.
        */
      while(WaitForMultipleObjectsEx(1, handles, FALSE, 0, FALSE)
            == WAIT_TIMEOUT) {
        /* get total size of file */
        length = 0;
        size.QuadPart = 0;
        size.LowPart = GetFileSize(handle, &length);
        if((size.LowPart != INVALID_FILE_SIZE) ||
           (GetLastError() == NO_ERROR)) {
          size.HighPart = length;
          /* get the current position within the file */
          pos.QuadPart = 0;
          pos.LowPart = SetFilePointer(handle, 0, &pos.HighPart,
                                       FILE_CURRENT);
          if((pos.LowPart != INVALID_SET_FILE_POINTER) ||
             (GetLastError() == NO_ERROR)) {
            /* compare position with size, abort if not equal */
            if(size.QuadPart == pos.QuadPart) {
              /* sleep and continue waiting */
              SleepEx(0, FALSE);
              continue;
            }
          }
        }
        /* there is some data available, stop waiting */
        break;
      }
      break;

    case FILE_TYPE_CHAR:
       /* The handle represents a character input, this means:
        * - WaitForMultipleObjectsEx will be signalled on any kind of input,
        *   including mouse and window size events we do not care about.
        *
        * Approach: Loop till either the internal event is signalled
        *           or we get signalled for an actual key-event.
        */
      while(WaitForMultipleObjectsEx(2, handles, FALSE, INFINITE, FALSE)
            == WAIT_OBJECT_0 + 1) {
        /* check if this is an actual console handle */
        length = 0;
        if(GetConsoleMode(handle, &length)) {
          /* retrieve an event from the console buffer */
          length = 0;
          if(PeekConsoleInput(handle, &inputrecord, 1, &length)) {
            /* check if the event is not an actual key-event */
            if(length == 1 && inputrecord.EventType != KEY_EVENT) {
              /* purge the non-key-event and continue waiting */
              ReadConsoleInput(handle, &inputrecord, 1, &length);
              continue;
            }
          }
        }
        /* there is some data available, stop waiting */
        break;
      }
      break;

    case FILE_TYPE_PIPE:
       /* The handle represents an anonymous or named pipe, this means:
        * - WaitForMultipleObjectsEx will always be signalled for it.
        * - peek into the pipe and retrieve the amount of data available.
        *
        * Approach: Loop till either the internal event is signalled
        *           or there is data in the pipe available for reading.
        */
      while(WaitForMultipleObjectsEx(1, handles, FALSE, 0, FALSE)
            == WAIT_TIMEOUT) {
        /* peek into the pipe and retrieve the amount of data available */
        length = 0;
        if(PeekNamedPipe(handle, NULL, 0, NULL, &length, NULL)) {
          /* if there is no data available, sleep and continue waiting */
          if(length == 0) {
            SleepEx(0, FALSE);
            continue;
          }
        }
        else {
          /* if the pipe has been closed, sleep and continue waiting */
          if(GetLastError() == ERROR_BROKEN_PIPE) {
            SleepEx(0, FALSE);
            continue;
          }
        }
        /* there is some data available, stop waiting */
        break;
      }
      break;

    default:
      /* The handle has an unknown type, try to wait on it */
      WaitForMultipleObjectsEx(2, handles, FALSE, INFINITE, FALSE);
      break;
  }

  return 0;
}