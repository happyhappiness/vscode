static int pinba_udp_read_callback_fn(int sock) /* {{{ */
{
  uint8_t buffer[PINBA_UDP_BUFFER_SIZE];
  size_t buffer_size;
  int status;

  while (42) {
    buffer_size = sizeof(buffer);
    status = recvfrom(sock, buffer, buffer_size - 1, MSG_DONTWAIT,
                      /* from = */ NULL, /* from len = */ 0);
    if (status < 0) {
      char errbuf[1024];

      if ((errno == EINTR)
#ifdef EWOULDBLOCK
          || (errno == EWOULDBLOCK)
#endif
          || (errno == EAGAIN)) {
        continue;
      }

      WARNING("pinba plugin: recvfrom(2) failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      return -1;
    } else if (status == 0) {
      DEBUG("pinba plugin: recvfrom(2) returned unexpected status zero.");
      return -1;
    } else /* if (status > 0) */
    {
      assert(((size_t)status) < buffer_size);
      buffer_size = (size_t)status;
      buffer[buffer_size] = 0;

      status = pinba_process_stats_packet(buffer, buffer_size);
      if (status != 0)
        DEBUG("pinba plugin: Parsing packet failed.");
      return status;
    }
  } /* while (42) */

  /* not reached */
  assert(23 == 42);
  return -1;
}