storeAppendPrintf(sentry, "average_select_fd_period = %f/fd\n",
                      f->select_fds > l->select_fds ?
                      (f->select_time - l->select_time) / (f->select_fds - l->select_fds)
                      : 0.0);