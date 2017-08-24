f(k->httpcode/100 == 2) {
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