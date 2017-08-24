{
    assert(!(pipe->flags & UV_HANDLE_NON_OVERLAPPED_PIPE));
    pipe->pipe.conn.ipc_pid = uv_parent_pid();
    assert(pipe->pipe.conn.ipc_pid != -1);
  }