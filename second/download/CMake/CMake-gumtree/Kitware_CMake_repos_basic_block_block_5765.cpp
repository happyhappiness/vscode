{
        /* read data from network */
        result = Curl_read(conn, sockfd, buf, data->set.buffer_size, &nread);
        /* read would've blocked. Loop again */
        if(result == CURLE_AGAIN)
          break;
        /* returned not-zero, this an error */
        else if(result) {
          keepon = FALSE;
          break;
        }
        /* returned zero but actually received 0 or less here,
           the server closed the connection and we bail out */
        else if(nread <= 0) {
          keepon = FALSE;
          break;
        }

        result = telrcv(conn, (unsigned char *) buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }

        /* Negotiate if the peer has started negotiating,
           otherwise don't. We don't want to speak telnet with
           non-telnet servers, like POP or SMTP. */
        if(tn->please_negotiate && !tn->already_negotiated) {
          negotiate(conn);
          tn->already_negotiated = 1;
        }
      }