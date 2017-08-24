f(keepon > TRUE) {
          /* This means we are currently ignoring a response-body */

          nread = 0; /* make next read start over in the read buffer */
          ptr = conn->connect_buffer;
          if(cl) {
            /* A Content-Length based body: simply count down the counter
               and make sure to break out of the loop when we're done! */
            cl--;
            if(cl <= 0) {
              keepon = FALSE;
              break;
            }
          }
          else {
            /* chunked-encoded body, so we need to do the chunked dance
               properly to know when the end of the body is reached */
            CHUNKcode r;
            ssize_t tookcareof = 0;

            /* now parse the chunked piece of data so that we can
               properly tell when the stream ends */
            r = Curl_httpchunk_read(conn, ptr, 1, &tookcareof);
            if(r == CHUNKE_STOP) {
              /* we're done reading chunks! */
              infof(data, "chunk reading DONE\n");
              keepon = FALSE;
              /* we did the full CONNECT treatment, go COMPLETE */
              conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;
            }
          }
          continue;
        }