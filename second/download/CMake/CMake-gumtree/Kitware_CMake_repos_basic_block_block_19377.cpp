{
  size_t i;
  struct pollfd* pe;

  /* If the fd is already in the set just update its events.  */
  assert(!loop->poll_fds_iterating);
  for (i = 0; i < loop->poll_fds_used; ++i) {
    if (loop->poll_fds[i].fd == w->fd) {
      loop->poll_fds[i].events = w->pevents;
      return;
    }
  }

  /* Otherwise, allocate a new slot in the set for the fd.  */
  uv__pollfds_maybe_resize(loop);
  pe = &loop->poll_fds[loop->poll_fds_used++];
  pe->fd = w->fd;
  pe->events = w->pevents;
}