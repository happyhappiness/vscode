{
  ssize_t len;
  char* buf;

  len = uv__fs_pathmax_size(req->path);
  buf = uv__malloc(len + 1);

  if (buf == NULL) {
    errno = ENOMEM;
    return -1;
  }

  if (realpath(req->path, buf) == NULL) {
    uv__free(buf);
    return -1;
  }

  req->ptr = buf;

  return 0;
}