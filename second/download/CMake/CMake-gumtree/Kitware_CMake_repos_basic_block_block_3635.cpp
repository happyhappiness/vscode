r(i=0; i < num; i++)
      ares_process_fd((ares_channel)data->state.resolver,
                      pfd[i].revents & (POLLRDNORM|POLLIN)?
                      pfd[i].fd:ARES_SOCKET_BAD,
                      pfd[i].revents & (POLLWRNORM|POLLOUT)?
                      pfd[i].fd:ARES_SOCKET_BAD)