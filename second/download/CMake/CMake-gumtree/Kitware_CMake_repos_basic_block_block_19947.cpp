{
    buf = uv_buf_init(NULL, 0);
    handle->alloc_cb((uv_handle_t*) handle, 64 * 1024, &buf);
    if (buf.base == NULL || buf.len == 0) {
      handle->recv_cb(handle, UV_ENOBUFS, &buf, NULL, 0);
      return;
    }
    assert(buf.base != NULL);

    h.msg_namelen = sizeof(peer);
    h.msg_iov = (void*) &buf;
    h.msg_iovlen = 1;

    do {
      nread = recvmsg(handle->io_watcher.fd, &h, 0);
    }
    while (nread == -1 && errno == EINTR);

    if (nread == -1) {
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      else
        handle->recv_cb(handle, -errno, &buf, NULL, 0);
    }
    else {
      const struct sockaddr *addr;
      if (h.msg_namelen == 0)
        addr = NULL;
      else
        addr = (const struct sockaddr*) &peer;

      flags = 0;
      if (h.msg_flags & MSG_TRUNC)
        flags |= UV_UDP_PARTIAL;

      handle->recv_cb(handle, nread, &buf, addr, flags);
    }
  }