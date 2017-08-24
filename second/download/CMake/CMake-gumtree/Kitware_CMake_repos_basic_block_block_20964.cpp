(uv_tcp_try_cancel_io(tcp) == 0) {
      /* In case of a shared socket, we try to cancel all outstanding I/O, */
      /* If that works, don't close the socket yet - wait for the read req to */
      /* return and close the socket in uv_tcp_endgame. */
      close_socket = 0;

    }