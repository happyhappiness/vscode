static int zookeeper_query(char *buffer, size_t buffer_size) {
  int sk, status;
  size_t buffer_fill;

  sk = zookeeper_connect();
  if (sk < 0) {
    ERROR("zookeeper: Could not connect to daemon");
    return -1;
  }

  status = (int)swrite(sk, "mntr\r\n", strlen("mntr\r\n"));
  if (status != 0) {
    char errbuf[1024];
    ERROR("zookeeper: write(2) failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(sk);
    return -1;
  }

  memset(buffer, 0, buffer_size);
  buffer_fill = 0;

  while ((status = (int)recv(sk, buffer + buffer_fill,
                             buffer_size - buffer_fill, /* flags = */ 0)) !=
         0) {
    if (status < 0) {
      char errbuf[1024];
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      ERROR("zookeeper: Error reading from socket: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      close(sk);
      return -1;
    }

    buffer_fill += (size_t)status;
  } /* while (recv) */

  status = 0;
  if (buffer_fill == 0) {
    WARNING("zookeeper: No data returned by MNTR command.");
    status = -1;
  }

  close(sk);
  return status;
}