{
    if (timeout != -1) {
      spec.tv_sec = timeout / 1000;
      spec.tv_nsec = (timeout % 1000) * 1000000;
    }

    if (pset != NULL)
      pthread_sigmask(SIG_BLOCK, pset, NULL);

    nfds = kevent(loop->backend_fd,
                  events,
                  nevents,
                  events,
                  ARRAY_SIZE(events),
                  timeout == -1 ? NULL : &spec);

    if (pset != NULL)
      pthread_sigmask(SIG_UNBLOCK, pset, NULL);

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

      if (timeout == 0)
        return;

      if (timeout == -1)
        continue;

      /* Interrupted by a signal. Update timeout and poll again. */
      goto update_timeout;
    }

    have_signals = 0;
    nevents = 0;

    assert(loop->watchers != NULL);
    loop->watchers[loop->nwatchers] = (void*) events;
    loop->watchers[loop->nwatchers + 1] = (void*) (uintptr_t) nfds;
    for (i = 0; i < nfds; i++) {
      ev = events + i;
      fd = ev->ident;
      /* Skip invalidated events, see uv__platform_invalidate_fd */
      if (fd == -1)
        continue;
      w = loop->watchers[fd];

      if (w == NULL) {
        /* File descriptor that we've stopped watching, disarm it. */
        /* TODO batch up */
        struct kevent events[1];

        EV_SET(events + 0, fd, ev->filter, EV_DELETE, 0, 0, 0);
        if (kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
          if (errno != EBADF && errno != ENOENT)
            abort();

        continue;
      }

      if (ev->filter == EVFILT_VNODE) {
        assert(w->events == POLLIN);
        assert(w->pevents == POLLIN);
        w->cb(loop, w, ev->fflags); /* XXX always uv__fs_event() */
        nevents++;
        continue;
      }

      revents = 0;

      if (ev->filter == EVFILT_READ) {
        if (w->pevents & POLLIN) {
          revents |= POLLIN;
          w->rcount = ev->data;
        } else {
          /* TODO batch up */
          struct kevent events[1];
          EV_SET(events + 0, fd, ev->filter, EV_DELETE, 0, 0, 0);
          if (kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
            if (errno != ENOENT)
              abort();
        }
      }

      if (ev->filter == EVFILT_WRITE) {
        if (w->pevents & POLLOUT) {
          revents |= POLLOUT;
          w->wcount = ev->data;
        } else {
          /* TODO batch up */
          struct kevent events[1];
          EV_SET(events + 0, fd, ev->filter, EV_DELETE, 0, 0, 0);
          if (kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
            if (errno != ENOENT)
              abort();
        }
      }

      if (ev->flags & EV_ERROR)
        revents |= POLLERR;

      if ((ev->flags & EV_EOF) && (w->pevents & UV__POLLRDHUP))
        revents |= UV__POLLRDHUP;

      if (revents == 0)
        continue;

      /* Run signal watchers last.  This also affects child process watchers
       * because those are implemented in terms of signal watchers.
       */
      if (w == &loop->signal_io_watcher)
        have_signals = 1;
      else
        w->cb(loop, w, revents);

      nevents++;
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

    diff = loop->time - base;
    if (diff >= (uint64_t) timeout)
      return;

    timeout -= diff;
  }