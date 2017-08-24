{
  DWORD error;

  if (handle->stream.conn.write_reqs_pending > 0)
    return UV_EAGAIN;

  if (uv_tty_write_bufs(handle, bufs, nbufs, &error))
    return uv_translate_sys_error(error);

  return uv__count_bufs(bufs, nbufs);
}