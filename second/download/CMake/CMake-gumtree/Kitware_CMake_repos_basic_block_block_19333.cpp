{
  struct sockaddr_un saddr;
  const char* pipe_fname = NULL;
  int sockfd = -1;
  int err;

  /* Already bound? */
  if (uv__stream_fd(handle) >= 0)
    return -EINVAL;

  /* Make a copy of the file name, it outlives this function's scope. */
  pipe_fname = uv__strdup(name);
  if (pipe_fname == NULL)
    return -ENOMEM;

  /* We've got a copy, don't touch the original any more. */
  name = NULL;

  err = uv__socket(AF_UNIX, SOCK_STREAM, 0);
  if (err < 0)
    goto err_socket;
  sockfd = err;

  memset(&saddr, 0, sizeof saddr);
  strncpy(saddr.sun_path, pipe_fname, sizeof(saddr.sun_path) - 1);
  saddr.sun_path[sizeof(saddr.sun_path) - 1] = '\0';
  saddr.sun_family = AF_UNIX;

  if (bind(sockfd, (struct sockaddr*)&saddr, sizeof saddr)) {
    err = -errno;
    /* Convert ENOENT to EACCES for compatibility with Windows. */
    if (err == -ENOENT)
      err = -EACCES;

    uv__close(sockfd);
    goto err_socket;
  }

  /* Success. */
  handle->flags |= UV_HANDLE_BOUND;
  handle->pipe_fname = pipe_fname; /* Is a strdup'ed copy. */
  handle->io_watcher.fd = sockfd;
  return 0;

err_socket:
  uv__free((void*)pipe_fname);
  return err;
}