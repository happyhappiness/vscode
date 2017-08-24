{
  int err;

  /* Return if already initialized. */
  if (loop->signal_pipefd[0] != -1)
    return 0;

  err = uv__make_pipe(loop->signal_pipefd, UV__F_NONBLOCK);
  if (err)
    return err;

  uv__io_init(&loop->signal_io_watcher,
              uv__signal_event,
              loop->signal_pipefd[0]);
  uv__io_start(loop, &loop->signal_io_watcher, POLLIN);

  return 0;
}