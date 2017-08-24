{
#if defined(__APPLE__)
  struct stat statbuf;
#endif /* defined(__APPLE__) */
  int fd;

  if (uv__is_active(handle))
    return -EINVAL;

  /* TODO open asynchronously - but how do we report back errors? */
  fd = open(path, O_RDONLY);
  if (fd == -1)
    return -errno;

  uv__handle_start(handle);
  uv__io_init(&handle->event_watcher, uv__fs_event, fd);
  handle->path = uv__strdup(path);
  handle->cb = cb;

#if defined(__APPLE__)
  if (uv__has_forked_with_cfrunloop)
    goto fallback;

  /* Nullify field to perform checks later */
  handle->cf_cb = NULL;
  handle->realpath = NULL;
  handle->realpath_len = 0;
  handle->cf_flags = flags;

  if (fstat(fd, &statbuf))
    goto fallback;
  /* FSEvents works only with directories */
  if (!(statbuf.st_mode & S_IFDIR))
    goto fallback;

  /* The fallback fd is no longer needed */
  uv__close(fd);
  handle->event_watcher.fd = -1;

  return uv__fsevents_init(handle);

fallback:
#endif /* defined(__APPLE__) */

  uv__io_start(handle->loop, &handle->event_watcher, POLLIN);

  return 0;
}