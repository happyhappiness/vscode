(server_pipe->handle != INVALID_HANDLE_VALUE) {
    uv_pipe_cleanup(loop, server_pipe);
  }