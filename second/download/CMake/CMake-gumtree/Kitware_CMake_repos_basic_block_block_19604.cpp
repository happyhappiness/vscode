{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    int fd_to_send = uv__handle_fd((uv_handle_t*) req->send_handle);
    union {
      char data[64];
      struct cmsghdr alias;
    } scratch;

    memset(&scratch, 0, sizeof(scratch));

    assert(fd_to_send >= 0);

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = iovcnt;
    msg.msg_flags = 0;

    msg.msg_control = &scratch.alias;
    msg.msg_controllen = CMSG_SPACE(sizeof(fd_to_send));

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd_to_send));

    /* silence aliasing warning */
    {
      void* pv = CMSG_DATA(cmsg);
      int* pi = pv;
      *pi = fd_to_send;
    }

    do {
      n = sendmsg(uv__stream_fd(stream), &msg, 0);
    }
#if defined(__APPLE__)
    /*
     * Due to a possible kernel bug at least in OS X 10.10 "Yosemite",
     * EPROTOTYPE can be returned while trying to write to a socket that is
     * shutting down. If we retry the write, we should get the expected EPIPE
     * instead.
     */
    while (n == -1 && (errno == EINTR || errno == EPROTOTYPE));
#else
    while (n == -1 && errno == EINTR);
#endif
  }