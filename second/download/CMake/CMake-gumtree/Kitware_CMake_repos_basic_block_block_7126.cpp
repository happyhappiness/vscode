e(len > (size_t)written) {
      ssize_t this_write;
      time_t timeleft;
      int what;

      this_write = 0;

      timeleft = Curl_timeleft(conn->data, NULL, FALSE);
      if(timeleft < 0) {
        /* we already got the timeout */
        failf(conn->data, "schannel: timed out sending data "
              "(bytes sent: %zd)", written);
        *err = CURLE_OPERATION_TIMEDOUT;
        written = -1;
        break;
      }

      what = SOCKET_WRITABLE(conn->sock[sockindex], timeleft);
      if(what < 0) {
        /* fatal error */
        failf(conn->data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        *err = CURLE_SEND_ERROR;
        written = -1;
        break;
      }
      else if(0 == what) {
        failf(conn->data, "schannel: timed out sending data "
              "(bytes sent: %zd)", written);
        *err = CURLE_OPERATION_TIMEDOUT;
        written = -1;
        break;
      }
      /* socket is writable */

      result = Curl_write_plain(conn, conn->sock[sockindex], data + written,
                                len - written, &this_write);
      if(result == CURLE_AGAIN)
        continue;
      else if(result != CURLE_OK) {
        *err = result;
        written = -1;
        break;
      }

      written += this_write;
    }