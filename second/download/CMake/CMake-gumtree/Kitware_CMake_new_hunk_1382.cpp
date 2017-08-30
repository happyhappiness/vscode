    CURLcode result;

    snprintf(buf, sizeof(data->state.buffer),

             "Content-Length: %" FORMAT_OFF_T "\r\n", expected_size);

    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);

    if(result)

      return result;



    result = Curl_client_write(conn, CLIENTWRITE_BOTH,

                               (char *)"Accept-ranges: bytes\r\n", 0);

    if(result)

      return result;



    if(fstated) {

      struct tm *tm;

      time_t clock = (time_t)statbuf.st_mtime;

#ifdef HAVE_GMTIME_R

      struct tm buffer;

      tm = (struct tm *)gmtime_r(&clock, &buffer);

#else

      tm = gmtime(&clock);

#endif

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

    }

    return result;

  }



  if (data->reqdata.resume_from <= expected_size)

    expected_size -= data->reqdata.resume_from;

  else {

    failf(data, "failed to resume file:// transfer");

    return CURLE_BAD_DOWNLOAD_RESUME;

  }



  if (fstated && (expected_size == 0))

    return CURLE_OK;

