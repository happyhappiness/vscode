(loop->poll_fds[i].fd == fd) {
      /* swap to last position and remove */
      --loop->poll_fds_used;
      uv__pollfds_swap(loop, i, loop->poll_fds_used);
      loop->poll_fds[loop->poll_fds_used].fd = -1;
      loop->poll_fds[loop->poll_fds_used].events = 0;
      loop->poll_fds[loop->poll_fds_used].revents = 0;
      return;
    }