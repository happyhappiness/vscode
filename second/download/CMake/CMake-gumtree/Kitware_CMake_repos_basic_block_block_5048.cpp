r(i=0; bvals[i].bv_val != NULL; i++) {
        int binval = 0;
        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\t", 1);
        if(writeerr) {
          *err = writeerr;
          return -1;
        }

       writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)bv.bv_val,
                                    bv.bv_len);
       if(writeerr) {
         *err = writeerr;
         return -1;
       }

        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)":", 1);
       if(writeerr) {
         *err = writeerr;
         return -1;
       }
        data->req.bytecount += bv.bv_len + 2;

        if(!binary) {
          /* check for leading or trailing whitespace */
          if(ISSPACE(bvals[i].bv_val[0]) ||
              ISSPACE(bvals[i].bv_val[bvals[i].bv_len-1]))
            binval = 1;
          else {
            /* check for unprintable characters */
            unsigned int j;
            for(j=0; j<bvals[i].bv_len; j++)
              if(!ISPRINT(bvals[i].bv_val[j])) {
                binval = 1;
                break;
              }
          }
        }
        if(binary || binval) {
          char *val_b64 = NULL;
          size_t val_b64_sz = 0;
          /* Binary value, encode to base64. */
          CURLcode error = Curl_base64_encode(data,
                                              bvals[i].bv_val,
                                              bvals[i].bv_len,
                                              &val_b64,
                                              &val_b64_sz);
          if(error) {
            ber_memfree(bvals);
            ber_free(ber, 0);
            ldap_msgfree(msg);
            *err = error;
            return -1;
          }
          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY,
                                       (char *)": ", 2);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          data->req.bytecount += 2;
          if(val_b64_sz > 0) {
            writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, val_b64,
                                     val_b64_sz);
            if(writeerr) {
              *err = writeerr;
              return -1;
            }
            free(val_b64);
            data->req.bytecount += val_b64_sz;
          }
        }
        else {
          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)" ", 1);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, bvals[i].bv_val,
                                       bvals[i].bv_len);
          if(writeerr) {
            *err = writeerr;
            return -1;
          }

          data->req.bytecount += bvals[i].bv_len + 1;
        }
        writeerr = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 0);
        if(writeerr) {
          *err = writeerr;
          return -1;
        }

        data->req.bytecount++;
      }