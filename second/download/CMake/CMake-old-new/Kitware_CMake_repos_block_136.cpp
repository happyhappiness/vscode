{
          host = aprintf("Host: %s\r\n", hostheader);
          if(!host) {
            free(hostheader);
            Curl_add_buffer_free(req_buffer);
            return CURLE_OUT_OF_MEMORY;
          }
        }