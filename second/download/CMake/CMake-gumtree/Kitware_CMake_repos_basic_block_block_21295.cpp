(err == WSAEWOULDBLOCK) {
        /* Kernel buffer empty */
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      }