{
  char pipe_name[64];
  SECURITY_ATTRIBUTES sa;
  DWORD server_access = 0;
  DWORD client_access = 0;
  HANDLE child_pipe = INVALID_HANDLE_VALUE;
  int err;

  if (flags & UV_READABLE_PIPE) {
    /* The server needs inbound access too, otherwise CreateNamedPipe() */
    /* won't give us the FILE_READ_ATTRIBUTES permission. We need that to */
    /* probe the state of the write buffer when we're trying to shutdown */
    /* the pipe. */
    server_access |= PIPE_ACCESS_OUTBOUND | PIPE_ACCESS_INBOUND;
    client_access |= GENERIC_READ | FILE_WRITE_ATTRIBUTES;
  }
  if (flags & UV_WRITABLE_PIPE) {
    server_access |= PIPE_ACCESS_INBOUND;
    client_access |= GENERIC_WRITE | FILE_READ_ATTRIBUTES;
  }

  /* Create server pipe handle. */
  err = uv_stdio_pipe_server(loop,
                             server_pipe,
                             server_access,
                             pipe_name,
                             sizeof(pipe_name));
  if (err)
    goto error;

  /* Create child pipe handle. */
  sa.nLength = sizeof sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;

  child_pipe = CreateFileA(pipe_name,
                           client_access,
                           0,
                           &sa,
                           OPEN_EXISTING,
                           server_pipe->ipc ? FILE_FLAG_OVERLAPPED : 0,
                           NULL);
  if (child_pipe == INVALID_HANDLE_VALUE) {
    err = GetLastError();
    goto error;
  }

#ifndef NDEBUG
  /* Validate that the pipe was opened in the right mode. */
  {
    DWORD mode;
    BOOL r = GetNamedPipeHandleState(child_pipe,
                                     &mode,
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL,
                                     0);
    assert(r == TRUE);
    assert(mode == (PIPE_READMODE_BYTE | PIPE_WAIT));
  }
#endif

  /* Do a blocking ConnectNamedPipe.  This should not block because we have */
  /* both ends of the pipe created. */
  if (!ConnectNamedPipe(server_pipe->handle, NULL)) {
    if (GetLastError() != ERROR_PIPE_CONNECTED) {
      err = GetLastError();
      goto error;
    }
  }

  /* The server end is now readable and/or writable. */
  if (flags & UV_READABLE_PIPE)
    server_pipe->flags |= UV_HANDLE_WRITABLE;
  if (flags & UV_WRITABLE_PIPE)
    server_pipe->flags |= UV_HANDLE_READABLE;

  *child_pipe_ptr = child_pipe;
  return 0;

 error:
  if (server_pipe->handle != INVALID_HANDLE_VALUE) {
    uv_pipe_cleanup(loop, server_pipe);
  }

  if (child_pipe != INVALID_HANDLE_VALUE) {
    CloseHandle(child_pipe);
  }

  return err;
}