{
      /* Modify, potentially removing events -- need to delete then add.
       * Could maybe mod if we knew for sure no events are removed, but
       * content of w->events is handled above as not reliable (falls back)
       * so may require a pollset_query() which would have to be pretty cheap
       * compared to a PS_DELETE to be worth optimizing. Alternatively, could
       * lazily remove events, squelching them in the mean time. */
      pc.cmd = PS_DELETE;
      if (pollset_ctl(loop->backend_fd, &pc, 1)) {
        assert(0 && "Failed to delete file descriptor (pc.fd) from pollset");
        abort();
      }
      pc.cmd = PS_ADD;
      if (pollset_ctl(loop->backend_fd, &pc, 1)) {
        assert(0 && "Failed to add file descriptor (pc.fd) to pollset");
        abort();
      }
    }