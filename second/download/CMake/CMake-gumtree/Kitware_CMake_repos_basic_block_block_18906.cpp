{
  ssize_t len;
  char* buf;

  len = uv__fs_pathmax_size(req->path);
  buf = uv__malloc(len + 1);

  if (buf == NULL) {
    errno = ENOMEM;
    return -1;
  }

  len = readlink(req->path, buf, len);

  if (len == -1) {
    uv__free(buf);
    return -1;
  }

  buf[len] = '\0';
  req->ptr = buf;

  return 0;
}