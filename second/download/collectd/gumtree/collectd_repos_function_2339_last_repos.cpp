static int wt_send_buffer(struct wt_callback *cb) {
  ssize_t status = 0;

  status = swrite(cb->sock_fd, cb->send_buf, strlen(cb->send_buf));
  if (status != 0) {
    char errbuf[1024];
    ERROR("write_tsdb plugin: send failed with status %zi (%s)", status,
          sstrerror(errno, errbuf, sizeof(errbuf)));

    close(cb->sock_fd);
    cb->sock_fd = -1;

    return -1;
  }

  return 0;
}