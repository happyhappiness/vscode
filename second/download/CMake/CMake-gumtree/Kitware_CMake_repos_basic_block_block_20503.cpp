{
  if (!handle->ipc) {
    return WSAEINVAL;
  }

  return uv_pipe_write_impl(loop, req, handle, bufs, nbufs, send_handle, cb);
}