{
    rc = recvmsg(fd, msg, flags | 0x40000000);  /* MSG_CMSG_CLOEXEC */
    if (rc != -1)
      return rc;
    if (errno != EINVAL)
      return -errno;
    rc = recvmsg(fd, msg, flags);
    if (rc == -1)
      return -errno;
    no_msg_cmsg_cloexec = 1;
  }