{
    /* See the comment for max_safe_timeout for an explanation of why
     * this is necessary.  Executive summary: kernel bug workaround.
     */
    if (sizeof(int32_t) == sizeof(long) && timeout >= max_safe_timeout)
      timeout = max_safe_timeout;

    if (sigmask != 0 && no_epoll_pwait != 0)
      if (pthread_sigmask(SIG_BLOCK, &sigset, NULL))
        abort();

    if (no_epoll_wait != 0 || (sigmask != 0 && no_epoll_pwait == 0)) {
      nfds = uv__epoll_pwait(loop->backend_fd,
                             events,
                             ARRAY_SIZE(events),
                             timeout,
                             sigmask);
      if (nfds == -1 && errno == ENOSYS)
        no_epoll_pwait = 1;
    } else {
      nfds = uv__epoll_wait(loop->backend_fd,
                            events,
                            ARRAY_SIZE(events),
                            timeout);
      if (nfds == -1 && errno == ENOSYS)
        no_epoll_wait = 1;
    }

    if (sigmask != 0 && no_epoll_pwait != 0)
      if (pthread_sigmask(SIG_UNBLOCK, &sigset, NULL))
        abort();

    /* Update loop->time unconditionally. It's tempting to skip the update when
     * timeout == 0 (i.e. non-blocking poll) but there is no guarantee that the
     * operating system didn't reschedule our process while in the syscall.
     */
    SAVE_ERRNO(uv__update_time(loop));

    if (nfds == 0) {
      assert(timeout != -1);

      if (timeout == 0)
        return;

      /* We may have been inside the system call for longer than |timeout|
       * milliseconds so we need to update the timestamp to avoid drift.
       */
      goto update_timeout;
    }

    if (nfds == -1) {
      if (errno == ENOSYS) {
        /* epoll_wait() or epoll_pwait() failed, try the other system call. */
        assert(no_epoll_wait == 0 || no_epoll_pwait == 0);
        continue;
      }

      if (errno != EINTR)
        abort();

      if (timeout == -1)
        continue;

      if (timeout == 0)
        return;

      /* Interrupted by a signal. Update timeout and poll again. */
      goto update_timeout;
    }

    have_signals = 0;
    nevents = 0;

    assert(loop->watchers != NULL);
    loop->watchers[loop->nwatchers] = (void*) events;
    loop->watchers[loop->nwatchers + 1] = (void*) (uintptr_t) nfds;
    for (i = 0; i < nfds; i++) {
      pe = events + i;
      fd = pe->data;

      /* Skip invalidated events, see uv__platform_invalidate_fd */
      if (fd == -1)
        continue;

      assert(fd >= 0);
      assert((unsigned) fd < loop->nwatchers);

      w = loop->watchers[fd];

      if (w == NULL) {
        /* File descriptor that we've stopped watching, disarm it.
         *
         * Ignore all errors because we may be racing with another thread
         * when the file descriptor is closed.
         */
        uv__epoll_ctl(loop->backend_fd, UV__EPOLL_CTL_DEL, fd, pe);
        continue;
      }

      /* Give users only events they're interested in. Prevents spurious
       * callbacks when previous callback invocation in this loop has stopped
       * the current watcher. Also, filters out events that users has not
       * requested us to watch.
       */
      pe->events &= w->pevents | POLLERR | POLLHUP;

      /* Work around an epoll quirk where it sometimes reports just the
       * EPOLLERR or EPOLLHUP event.  In order to force the event loop to
       * move forward, we merge in the read/write events that the watcher
       * is interested in; uv__read() and uv__write() will then deal with
       * the error or hangup in the usual fashion.
       *
       * Note to self: happens when epoll reports EPOLLIN|EPOLLHUP, the user
       * reads the available data, calls uv_read_stop(), then sometime later
       * calls uv_read_start() again.  By then, libuv has forgotten about the
       * hangup and the kernel won't report EPOLLIN again because there's
       * nothing left to read.  If anything, libuv is to blame here.  The
       * current hack is just a quick bandaid; to properly fix it, libuv
       * needs to remember the error/hangup event.  We should get that for
       * free when we switch over to edge-triggered I/O.
       */
      if (pe->events == POLLERR || pe->events == POLLHUP)
        pe->events |= w->pevents & (POLLIN | POLLOUT);

      if (pe->events != 0) {
        /* Run signal watchers last.  This also affects child process watchers
         * because those are implemented in terms of signal watchers.
         */
        if (w == &loop->signal_io_watcher)
          have_signals = 1;
        else
          w->cb(loop, w, pe->events);

        nevents++;
      }
    }

    if (have_signals != 0)
      loop->signal_io_watcher.cb(loop, &loop->signal_io_watcher, POLLIN);

    loop->watchers[loop->nwatchers] = NULL;
    loop->watchers[loop->nwatchers + 1] = NULL;

    if (have_signals != 0)
      return;  /* Event loop should cycle now so don't poll again. */

    if (nevents != 0) {
      if (nfds == ARRAY_SIZE(events) && --count != 0) {
        /* Poll for more events but don't block this time. */
        timeout = 0;
        continue;
      }
      return;
    }

    if (timeout == 0)
      return;

    if (timeout == -1)
      continue;

update_timeout:
    assert(timeout > 0);

    real_timeout -= (loop->time - base);
    if (real_timeout <= 0)
      return;

    timeout = real_timeout;
  }