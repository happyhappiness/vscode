{
    time_t filetime;
    struct tm buffer;
    const struct tm *tm = &buffer;
    snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
    if(result)
      return result;

    result = Curl_client_write(conn, CLIENTWRITE_BOTH,
                               (char *)"Accept-ranges: bytes\r\n", 0);
    if(result)
      return result;

    filetime = (time_t)statbuf.st_mtime;
    result = Curl_gmtime(filetime, &buffer);
    if(result)
      return result;

    /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
    snprintf(buf, BUFSIZE-1,
             "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
             Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
             tm->tm_mday,
             Curl_month[tm->tm_mon],
             tm->tm_year + 1900,
             tm->tm_hour,
             tm->tm_min,
             tm->tm_sec);
    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
    if(!result)
      /* set the file size to make it available post transfer */
      Curl_pgrsSetDownloadSize(data, expected_size);
    return result;
  }