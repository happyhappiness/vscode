(handle->pipe.conn.pending_ipc_info.queue_len == 0)
    return UV_UNKNOWN_HANDLE;
  else
    return UV_TCP;