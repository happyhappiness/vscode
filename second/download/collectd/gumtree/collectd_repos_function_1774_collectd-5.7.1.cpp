static int cconn_validate_revents(struct cconn *io, int revents) {
  if (revents & POLLERR) {
    ERROR("ceph plugin: cconn_validate_revents(name=%s): got POLLERR",
          io->d->name);
    return -EIO;
  }
  switch (io->state) {
  case CSTATE_WRITE_REQUEST:
    return (revents & POLLOUT) ? 0 : -EINVAL;
  case CSTATE_READ_VERSION:
  case CSTATE_READ_AMT:
  case CSTATE_READ_JSON:
    return (revents & POLLIN) ? 0 : -EINVAL;
  default:
    ERROR("ceph plugin: cconn_validate_revents(name=%s) got to "
          "illegal state on line %d",
          io->d->name, __LINE__);
    return -EDOM;
  }
}