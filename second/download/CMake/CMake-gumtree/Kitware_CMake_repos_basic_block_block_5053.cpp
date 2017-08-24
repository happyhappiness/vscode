f(val_b64_sz > 0) {
            writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, val_b64,
                                     val_b64_sz);
            if(writeerr) {
              *err = writeerr;
              return -1;
            }
            free(val_b64);
            data->req.bytecount += val_b64_sz;
          }