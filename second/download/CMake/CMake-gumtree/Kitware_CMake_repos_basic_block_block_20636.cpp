{
    /* The server needs inbound access too, otherwise CreateNamedPipe() */
    /* won't give us the FILE_READ_ATTRIBUTES permission. We need that to */
    /* probe the state of the write buffer when we're trying to shutdown */
    /* the pipe. */
    server_access |= PIPE_ACCESS_OUTBOUND | PIPE_ACCESS_INBOUND;
    client_access |= GENERIC_READ | FILE_WRITE_ATTRIBUTES;
  }