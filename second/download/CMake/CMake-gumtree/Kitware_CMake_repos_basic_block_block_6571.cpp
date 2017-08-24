{
        case errSSLWouldBlock:
          /* Data was buffered but not sent, we have to tell the caller
             to try sending again, and remember how much was buffered */
          connssl->ssl_write_buffered_length = len;
          *curlcode = CURLE_AGAIN;
          return -1L;
        default:
          failf(conn->data, "SSLWrite() returned error %d", err);
          *curlcode = CURLE_SEND_ERROR;
          return -1L;
      }