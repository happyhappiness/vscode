     information. Which for FILE can't be much more than the file size and

     date. */

  if(data->set.opt_no_body && data->set.include_header && fstated) {

    time_t filetime;

    struct tm buffer;

    const struct tm *tm = &buffer;

    snprintf(buf, sizeof(data->state.buffer),

             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);

    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);

