(w->pevents & POLLOUT) {
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