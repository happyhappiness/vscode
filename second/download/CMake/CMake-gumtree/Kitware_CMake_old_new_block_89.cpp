{
      snprintf(buf, sizeof(data->state.buffer),
               "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);
      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }