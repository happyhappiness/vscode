{
  int result;
  DWORD bytes;

  if (handle->stream.conn.write_reqs_pending > 0)
    return UV_EAGAIN;

  result = WSASend(handle->socket,
                   (WSABUF*) bufs,
                   nbufs,
                   &bytes,
                   0,
                   NULL,
                   NULL);

  if (result == SOCKET_ERROR)
    return uv_translate_sys_error(WSAGetLastError());
  else
    return bytes;
}