(errno == EAGAIN || errno == EWOULDBLOCK)
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      else
        handle->recv_cb(handle, -errno, &buf, NULL, 0)