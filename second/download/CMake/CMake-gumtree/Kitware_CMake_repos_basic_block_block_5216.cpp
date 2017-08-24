{
    buf[decoded_len] = '\n';
    Curl_debug(conn->data, CURLINFO_HEADER_IN, buf, decoded_len + 1, conn);
  }