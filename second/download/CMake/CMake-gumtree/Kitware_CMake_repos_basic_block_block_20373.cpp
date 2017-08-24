{
    uv_unique_pipe_name(ptr, name, nameSize);

    pipeHandle = CreateNamedPipeA(name,
      access | FILE_FLAG_OVERLAPPED | FILE_FLAG_FIRST_PIPE_INSTANCE,
      PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 65536, 65536, 0,
      NULL);

    if (pipeHandle != INVALID_HANDLE_VALUE) {
      /* No name collisions.  We're done. */
      break;
    }

    err = GetLastError();
    if (err != ERROR_PIPE_BUSY && err != ERROR_ACCESS_DENIED) {
      goto error;
    }

    /* Pipe name collision.  Increment the pointer and try again. */
    ptr++;
  }