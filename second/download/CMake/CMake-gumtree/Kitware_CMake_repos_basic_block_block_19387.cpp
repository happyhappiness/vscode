{
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