{
      line[len] = '\n';
      result = Curl_client_write(conn, CLIENTWRITE_BODY, line, len + 1);
      line[len] = '\0';
    }