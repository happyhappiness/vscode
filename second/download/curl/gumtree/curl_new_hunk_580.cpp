
        if(Curl_GetFTPResponse(&nread, conn, NULL)) {
          ret = -1;
          break;
        }

        if(data->state.buffer[0] != '2' && data->state.buffer[0] != '3') {
          Curl_infof(data, "Server didn't accept auth data\n");
          ret = AUTH_ERROR;
          break;
        }

        p = data->state.buffer + 4;
        p = strstr(p, "ADAT=");
        if(p) {
          result = Curl_base64_decode(p + 5,
                                      (unsigned char **)&_gssresp.value,
                                      &_gssresp.length);
          if(result) {
            Curl_failf(data,"base64-decoding: %s", curl_easy_strerror(result));
            ret = AUTH_CONTINUE;
            break;
          }
        }

        gssresp = &_gssresp;
