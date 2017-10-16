
        if(Curl_GetFTPResponse(&nread, conn, NULL)) {
          ret = -1;
          break;
        }

        if(data->state.buffer[0] != '2' && data->state.buffer[0] != '3'){
          Curl_infof(data, "Server didn't accept auth data\n");
          ret = AUTH_ERROR;
          break;
        }

        p = data->state.buffer + 4;
        p = strstr(p, "ADAT=");
        if(p) {
          _gssresp.length = Curl_base64_decode(p + 5, (unsigned char **)
                                               &_gssresp.value);
          if(_gssresp.length < 1) {
            Curl_failf(data, "Out of memory base64-encoding\n");
            ret = AUTH_CONTINUE;
            break;
          }
        }

        gssresp = &_gssresp;
