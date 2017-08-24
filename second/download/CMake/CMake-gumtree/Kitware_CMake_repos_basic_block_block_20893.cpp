{
  int result;

  if (handle->socket == INVALID_SOCKET) {
    return UV_EINVAL;
  }

  if (handle->delayed_error) {
    return uv_translate_sys_error(handle->delayed_error);
  }

  result = getsockname(handle->socket, name, namelen);
  if (result != 0) {
    return uv_translate_sys_error(WSAGetLastError());
  }

  return 0;
}