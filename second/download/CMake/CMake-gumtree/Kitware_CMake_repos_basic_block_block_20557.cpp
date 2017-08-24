{
  if (!handle->ipc)
    return 0;
  return handle->pipe.conn.pending_ipc_info.queue_len;
}