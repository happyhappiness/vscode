{
  int r;
  int fd;
  socklen_t len;

  if (handle == NULL || value == NULL)
    return -EINVAL;

  if (handle->type == UV_TCP || handle->type == UV_NAMED_PIPE)
    fd = uv__stream_fd((uv_stream_t*) handle);
  else if (handle->type == UV_UDP)
    fd = ((uv_udp_t *) handle)->io_watcher.fd;
  else
    return -ENOTSUP;

  len = sizeof(*value);

  if (*value == 0)
    r = getsockopt(fd, SOL_SOCKET, optname, value, &len);
  else
    r = setsockopt(fd, SOL_SOCKET, optname, (const void*) value, len);

  if (r < 0)
    return -errno;

  return 0;
}