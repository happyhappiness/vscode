    CURLcode result;
    snprintf(buf, sizeof(data->state.buffer),
             "Content-Length: %" FORMAT_OFF_T "\r\n", expected_size);
    result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
    if(result)
      return result;

    result = Curl_client_write(data, CLIENTWRITE_BOTH,
                               (char *)"Accept-ranges: bytes\r\n", 0);
    if(result)
      return result;

#ifdef HAVE_STRFTIME
    if(fstated) {
      struct tm *tm;
      time_t cuClock = (time_t)statbuf.st_mtime;
#ifdef HAVE_GMTIME_R
      struct tm buffer;
      tm = (struct tm *)gmtime_r(&cuClock, &buffer);
#else
      tm = gmtime(&cuClock);
#endif
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",
               tm);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
    }
#endif
    return result;
  }

  /* Added by Dolbneff A.V & Spiridonoff A.V */
  if (conn->resume_from <= expected_size)
    expected_size -= conn->resume_from;
  else
    /* Is this error code suitable in such situation? */
    return CURLE_FTP_BAD_DOWNLOAD_RESUME;

  if (fstated && (expected_size == 0))
    return CURLE_OK;
