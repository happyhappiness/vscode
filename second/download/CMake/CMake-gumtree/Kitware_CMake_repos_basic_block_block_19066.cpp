{
        if (kevent(loop->backend_fd, events, nevents, NULL, 0, NULL))
          abort();
        nevents = 0;
      }