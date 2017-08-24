f((checkprefix("WWW-Authenticate:", line_start) &&
            (401 == k->httpcode)) ||
           (checkprefix("Proxy-authenticate:", line_start) &&
            (407 == k->httpcode))) {

          bool proxy = (k->httpcode == 407) ? TRUE : FALSE;
          char *auth = Curl_copy_header_value(line_start);
          if(!auth)
            return CURLE_OUT_OF_MEMORY;

          result = Curl_http_input_auth(conn, proxy, auth);

          free(auth);

          if(result)
            return result;
        }
        else if(checkprefix("Content-Length:", line_start)) {
          if(k->httpcode/100 == 2) {
            /* A client MUST ignore any Content-Length or Transfer-Encoding
               header fields received in a successful response to CONNECT.
               "Successful" described as: 2xx (Successful). RFC 7231 4.3.6 */
            infof(data, "Ignoring Content-Length in CONNECT %03d response\n",
                  k->httpcode);
          }
          else {
            cl = curlx_strtoofft(line_start +
                                 strlen("Content-Length:"), NULL, 10);
          }
        }
        else if(Curl_compareheader(line_start, "Connection:", "close"))
          closeConnection = TRUE;
        else if(checkprefix("Transfer-Encoding:", line_start)) {
          if(k->httpcode/100 == 2) {
            /* A client MUST ignore any Content-Length or Transfer-Encoding
               header fields received in a successful response to CONNECT.
               "Successful" described as: 2xx (Successful). RFC 7231 4.3.6 */
            infof(data, "Ignoring Transfer-Encoding in "
                  "CONNECT %03d response\n", k->httpcode);
          }
          else if(Curl_compareheader(line_start,
                                     "Transfer-Encoding:", "chunked")) {
            infof(data, "CONNECT responded chunked\n");
            chunked_encoding = TRUE;
            /* init our chunky engine */
            Curl_httpchunk_init(conn);
          }
        }
        else if(Curl_compareheader(line_start, "Proxy-Connection:", "close"))
          closeConnection = TRUE;
        else if(2 == sscanf(line_start, "HTTP/1.%d %d",
                            &subversion,
                            &k->httpcode)) {
          /* store the HTTP code from the proxy */
          data->info.httpproxycode = k->httpcode;
        }