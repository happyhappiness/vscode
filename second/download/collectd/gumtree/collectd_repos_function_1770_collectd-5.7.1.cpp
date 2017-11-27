static int cconn_connect(struct cconn *io) {
  struct sockaddr_un address = {0};
  int flags, fd, err;
  if (io->state != CSTATE_UNCONNECTED) {
    ERROR("ceph plugin: cconn_connect: io->state != CSTATE_UNCONNECTED");
    return -EDOM;
  }
  fd = socket(PF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) {
    err = -errno;
    ERROR("ceph plugin: cconn_connect: socket(PF_UNIX, SOCK_STREAM, 0) "
          "failed: error %d",
          err);
    return err;
  }
  address.sun_family = AF_UNIX;
  snprintf(address.sun_path, sizeof(address.sun_path), "%s", io->d->asok_path);
  RETRY_ON_EINTR(err, connect(fd, (struct sockaddr *)&address,
                              sizeof(struct sockaddr_un)));
  if (err < 0) {
    ERROR("ceph plugin: cconn_connect: connect(%d) failed: error %d", fd, err);
    close(fd);
    return err;
  }

  flags = fcntl(fd, F_GETFL, 0);
  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0) {
    err = -errno;
    ERROR("ceph plugin: cconn_connect: fcntl(%d, O_NONBLOCK) error %d", fd,
          err);
    close(fd);
    return err;
  }
  io->asok = fd;
  io->state = CSTATE_WRITE_REQUEST;
  io->amt = 0;
  io->json_len = 0;
  io->json = NULL;
  return 0;
}