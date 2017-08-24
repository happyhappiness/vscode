(err == WSAECONNRESET || err == WSAENETRESET) {
      /* A previous sendto operation failed; ignore this error. If */
      /* zero-reading we need to call WSARecv/WSARecvFrom _without_ the */
      /* MSG_PEEK flag to clear out the error queue. For nonzero reads, */
      /* immediately queue a new receive. */
      if (!(handle->flags & UV_HANDLE_ZERO_READ)) {
        goto done;
      }
    }