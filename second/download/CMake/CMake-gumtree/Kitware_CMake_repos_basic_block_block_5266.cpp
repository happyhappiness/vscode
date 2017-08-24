f(readfd1 != CURL_SOCKET_BAD) {
    pfd[num].fd = readfd1;
    pfd[num].events = POLLRDNORM|POLLIN|POLLRDBAND|POLLPRI;
    pfd[num].revents = 0;
    num++;
  }