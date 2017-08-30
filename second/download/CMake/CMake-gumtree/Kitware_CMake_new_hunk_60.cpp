    time_t filetime;

    struct tm buffer;

    const struct tm *tm = &buffer;

    char header[80];

    snprintf(header, sizeof(header),

             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);

    result = Curl_client_write(conn, CLIENTWRITE_BOTH, header, 0);

    if(result)

      return result;



