f(pfd[num].revents & (POLLERR|POLLHUP|POLLNVAL))
      ret |= CURL_CSELECT_ERR