{
      err = WSAGetLastError();
      if (err == WSAEMSGSIZE) {
        /* Message truncated */
        handle->recv_cb(handle,
                        bytes,
                        &buf,
                        (const struct sockaddr*) &from,
                        UV_UDP_PARTIAL);
      } else if (err == WSAEWOULDBLOCK) {
        /* Kernel buffer empty */
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      } else if (err == WSAECONNRESET || err == WSAENETRESET) {
        /* WSAECONNRESET/WSANETRESET is ignored because this just indicates
         * that a previous sendto operation failed.
         */
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      } else {
        /* Any other error that we want to report back to the user. */
        uv_udp_recv_stop(handle);
        handle->recv_cb(handle, uv_translate_sys_error(err), &buf, NULL, 0);
      }
    }