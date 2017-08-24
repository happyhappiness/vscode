{

          bool proxy = (k->httpcode == 407) ? TRUE : FALSE;
          char *auth = Curl_copy_header_value(line_start);
          if(!auth)
            return CURLE_OUT_OF_MEMORY;

          result = Curl_http_input_auth(conn, proxy, auth);

          free(auth);

          if(result)
            return result;
        }