{
          infof(data, "schannel: sending next handshake data: "
                "sending %lu bytes...\n", outbuf[i].cbBuffer);

          /* send handshake token to server */
          result = Curl_write_plain(conn, conn->sock[sockindex],
                                    outbuf[i].pvBuffer, outbuf[i].cbBuffer,
                                    &written);
          if((result != CURLE_OK) ||
             (outbuf[i].cbBuffer != (size_t) written)) {
            failf(data, "schannel: failed to send next handshake data: "
                  "sent %zd of %lu bytes", written, outbuf[i].cbBuffer);
            return CURLE_SSL_CONNECT_ERROR;
          }
        }