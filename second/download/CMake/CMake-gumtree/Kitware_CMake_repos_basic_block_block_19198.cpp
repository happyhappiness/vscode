do
      size = read(loop->inotify_fd, buf, sizeof(buf));
    while (size == -1 && errno == EINTR);