    time_t filetime;
    struct tm buffer;
    const struct tm *tm = &buffer;
    snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
    if(result)
      return result;

