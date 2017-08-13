                                      (unsigned char **)&_gssresp.value,
                                      &_gssresp.length);
          if(result) {
            Curl_failf(data, "base64-decoding: %s",
                       curl_easy_strerror(result));
            ret = AUTH_CONTINUE;
            break;
          }
