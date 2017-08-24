(i = 0; i < queued_fds->offset; i++)
      uv__close(queued_fds->fds[i])