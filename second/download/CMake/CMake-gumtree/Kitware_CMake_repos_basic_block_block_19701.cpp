{
    if (timeout != -1) {
      spec.tv_sec = timeout / 1000;
      spec.tv_nsec = (timeout % 1000) * 1000000;
    }

    /* Work around a kernel bug where nfds is not updated. */
    events[0].portev_source = 0;

    nfds = 1;
    saved_errno = 0;

    if (pset != NULL)
      pthread_sigmask(SIG_BLOCK, pset, NULL);

    err = port_getn(loop->backend_fd,
                    events,
                    ARRAY_SIZE(events),
                    &nfds,
                    timeout == -1 ? NULL : &spec);

    if (pset != NULL)
      pthread_sigmask(SIG_UNBLOCK, pset, NULL);

    if (err) {
      /* Work around another kernel bug: port_getn() may return events even
       * on error.
       */
      if (errno == EINTR || errno == ETIME)
        saved_errno = errno;
      else
        abort();
    }

    /* Update loop->time unconditionally. It's tempting to skip the update when
     * timeout == 0 (i.e. non-blocking poll) but there is no guarantee that the
     * operating system didn't reschedule our process while in the syscall.
     */
    SAVE_ERRNO(uv__update_time(loop));

    if (events[0].portev_source == 0) {
      if (timeout == 0)
        return;

      if (timeout == -1)
        continue;

      goto update_timeout;
    }

    if (nfds == 0) {
      assert(timeout != -1);
      return;
    }

    have_signals = 0;
    nevents = 0;

    assert(loop->watchers != NULL);
    loop->watchers[loop->nwatchers] = (void*) events;
    loop->watchers[loop->nwatchers + 1] = (void*) (uintptr_t) nfds;
    for (i = 0; i < nfds; i++) {
      pe = events + i;
      fd = pe->portev_object;

      /* Skip invalidated events, see uv__platform_invalidate_fd */
      if (fd == -1)
        continue;

      assert(fd >= 0);
      assert((unsigned) fd < loop->nwatchers);

      w = loop->watchers[fd];

      /* File descriptor that we've stopped watching, ignore. */
      if (w == NULL)
        continue;

      /* Run signal watchers last.  This also affects child process watchers
       * because those are implemented in terms of signal watchers.
       */
      if (w == &loop->signal_io_watcher)
        have_signals = 1;
      else
        w->cb(loop, w, pe->portev_events);

      nevents++;

      if (w != loop->watchers[fd])
        continue;  /* Disabled by callback. */

      /* Events Ports operates in oneshot mode, rearm timer on next run. */
      if (w->pevents != 0 && QUEUE_EMPTY(&w->watcher_queue))
        QUEUE_INSERT_TAIL(&loop->watcher_queue, &w->watcher_queue);
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

    if (saved_errno == ETIME) {
      assert(timeout != -1);
      return;
    }

    if (timeout == 0)
      return;

    if (timeout == -1)
      continue;

update_timeout:
    assert(timeout > 0);

    diff = loop->time - base;
    if (diff >= (uint64_t) timeout)
      return;

    timeout -= diff;
  }