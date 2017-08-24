{
    if (pset != NULL)
      if (pthread_sigmask(SIG_BLOCK, pset, NULL))
        abort();
    nfds = poll(loop->poll_fds, (nfds_t)loop->poll_fds_used, timeout);
    if (pset != NULL)
      if (pthread_sigmask(SIG_UNBLOCK, pset, NULL))
        abort();

    /* Update loop->time unconditionally. It's tempting to skip the update when
     * timeout == 0 (i.e. non-blocking poll) but there is no guarantee that the
     * operating system didn't reschedule our process while in the syscall.
     */
    SAVE_ERRNO(uv__update_time(loop));

    if (nfds == 0) {
      assert(timeout != -1);
      return;
    }

    if (nfds == -1) {
      if (errno != EINTR)
        abort();

      if (timeout == -1)
        continue;

      if (timeout == 0)
        return;

      /* Interrupted by a signal. Update timeout and poll again. */
      goto update_timeout;
    }

    /* Tell uv__platform_invalidate_fd not to manipulate our array
     * while we are iterating over it.
     */
    loop->poll_fds_iterating = 1;

    /* Initialize a count of events that we care about.  */
    nevents = 0;
    have_signals = 0;

    /* Loop over the entire poll fds array looking for returned events.  */
    for (i = 0; i < loop->poll_fds_used; i++) {
      pe = loop->poll_fds + i;
      fd = pe->fd;

      /* Skip invalidated events, see uv__platform_invalidate_fd.  */
      if (fd == -1)
        continue;

      assert(fd >= 0);
      assert((unsigned) fd < loop->nwatchers);

      w = loop->watchers[fd];

      if (w == NULL) {
        /* File descriptor that we've stopped watching, ignore.  */
        uv__platform_invalidate_fd(loop, fd);
        continue;
      }

      /* Filter out events that user has not requested us to watch
       * (e.g. POLLNVAL).
       */
      pe->revents &= w->pevents | POLLERR | POLLHUP;

      if (pe->revents != 0) {
        /* Run signal watchers last.  */
        if (w == &loop->signal_io_watcher) {
          have_signals = 1;
        } else {
          w->cb(loop, w, pe->revents);
        }

        nevents++;
      }
    }

    if (have_signals != 0)
      loop->signal_io_watcher.cb(loop, &loop->signal_io_watcher, POLLIN);

    loop->poll_fds_iterating = 0;

    /* Purge invalidated fds from our poll fds array.  */
    uv__pollfds_del(loop, -1);

    if (have_signals != 0)
      return;  /* Event loop should cycle now so don't poll again. */

    if (nevents != 0)
      return;

    if (timeout == 0)
      return;

    if (timeout == -1)
      continue;

update_timeout:
    assert(timeout > 0);

    time_diff = loop->time - time_base;
    if (time_diff >= (uint64_t) timeout)
      return;

    timeout -= time_diff;
  }