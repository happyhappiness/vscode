{
  loop->fs_fd = -1;

  /* Passing maxfd of -1 should mean the limit is determined
   * by the user's ulimit or the global limit as per the doc */
  loop->backend_fd = pollset_create(-1);

  if (loop->backend_fd == -1)
    return -1;

  return 0;
}