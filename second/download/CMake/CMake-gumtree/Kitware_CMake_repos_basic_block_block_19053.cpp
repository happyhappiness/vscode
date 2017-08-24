{
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