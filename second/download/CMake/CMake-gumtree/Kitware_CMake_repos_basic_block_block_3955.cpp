{
          /* socket activity, tell libcurl */
          int act = poll2cselect(fds[i].revents); /* convert */
          infof(multi->easyp, "call curl_multi_socket_action(socket %d)\n",
                fds[i].fd);
          mcode = curl_multi_socket_action(multi, fds[i].fd, act,
                                           &ev->running_handles);
        }