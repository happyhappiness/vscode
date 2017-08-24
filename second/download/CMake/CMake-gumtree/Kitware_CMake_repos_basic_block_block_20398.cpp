{
    handle->flags &= ~UV_HANDLE_PIPE_READ_CANCELABLE;
    uv_mutex_destroy(&handle->pipe.conn.readfile_mutex);
  }