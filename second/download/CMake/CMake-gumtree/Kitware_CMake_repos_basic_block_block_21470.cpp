{
  char buf[MAXHOSTNAMELEN + 1];
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  uv__once_init(); /* Initialize winsock */

  if (gethostname(buf, sizeof(buf)) != 0)
    return uv_translate_sys_error(WSAGetLastError());

  buf[sizeof(buf) - 1] = '\0'; /* Null terminate, just to be safe. */
  len = strlen(buf);

  if (len >= *size) {
    *size = len + 1;
    return UV_ENOBUFS;
  }

  memcpy(buffer, buf, len + 1);
  *size = len;
  return 0;
}