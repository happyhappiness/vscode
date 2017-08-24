(uv__epoll_ctl(loop->backend_fd, UV__EPOLL_CTL_DEL, fd, &e))
      abort()