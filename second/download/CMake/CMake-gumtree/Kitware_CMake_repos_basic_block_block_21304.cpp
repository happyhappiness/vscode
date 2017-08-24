{
    DWORD err = GET_REQ_SOCK_ERROR(req);
    if (err == WSAEMSGSIZE) {
      /* Not a real error, it just indicates that the received packet */
      /* was bigger than the receive buffer. */
    } else if (err == WSAECONNRESET || err == WSAENETRESET) {
      /* A previous sendto operation failed; ignore this error. If */
      /* zero-reading we need to call WSARecv/WSARecvFrom _without_ the */
      /* MSG_PEEK flag to clear out the error queue. For nonzero reads, */
      /* immediately queue a new receive. */
      if (!(handle->flags & UV_HANDLE_ZERO_READ)) {
        goto done;
      }
    } else {
      /* A real error occurred. Report the error to the user only if we're */
      /* currently reading. */
      if (handle->flags & UV_HANDLE_READING) {
        uv_udp_recv_stop(handle);
        buf = (handle->flags & UV_HANDLE_ZERO_READ) ?
              uv_buf_init(NULL, 0) : handle->recv_buffer;
        handle->recv_cb(handle, uv_translate_sys_error(err), &buf, NULL, 0);
      }
      goto done;
    }
  }