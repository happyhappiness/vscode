{
    wfds.fd_count = 1;
    wfds.fd_array[0] = handle->socket;
    efds.fd_count = 1;
    efds.fd_array[0] = handle->socket;
  }