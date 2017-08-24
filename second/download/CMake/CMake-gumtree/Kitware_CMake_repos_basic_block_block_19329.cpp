{
      if (errno != EEXIST)
        abort();

      assert(op == UV__EPOLL_CTL_ADD);

      /* We've reactivated a file descriptor that's been watched before. */
      if (epoll_ctl(loop->ep, UV__EPOLL_CTL_MOD, w->fd, &e))
        abort();
    }