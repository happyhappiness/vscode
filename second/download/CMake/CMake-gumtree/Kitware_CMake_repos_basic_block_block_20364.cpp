{
      uv_mutex_init(&handle->pipe.conn.readfile_mutex);
      handle->flags |= UV_HANDLE_PIPE_READ_CANCELABLE;
  }