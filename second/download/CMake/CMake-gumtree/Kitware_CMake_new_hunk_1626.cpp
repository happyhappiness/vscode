    result = ftp_getsize(conn, ftp->file, &filesize);



    if(CURLE_OK == result) {

      snprintf(buf, sizeof(data->state.buffer),

               "Content-Length: %" FORMAT_OFF_T "\r\n", filesize);

      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);

      if(result)

        return result;

    }



    /* Determine if server can respond to REST command and therefore

       whether it can do a range */

    FTPSENDF(conn, "REST 0", NULL);

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);



    if ((CURLE_OK == result) && (ftpcode == 350)) {

      result = Curl_client_write(data, CLIENTWRITE_BOTH,

                                 (char *)"Accept-ranges: bytes\r\n", 0);

      if(result)

        return result;

    }



    /* If we asked for a time of the file and we actually got one as

       well, we "emulate" a HTTP-style header in our output. */



#ifdef HAVE_STRFTIME

    if(data->set.get_filetime && (data->info.filetime>=0) ) {

      struct tm *tm;

      time_t clock = (time_t)data->info.filetime;

#ifdef HAVE_GMTIME_R

      struct tm buffer;

      tm = (struct tm *)gmtime_r(&clock, &buffer);

#else

      tm = gmtime(&clock);

#endif

      /* format: "Tue, 15 Nov 1994 12:45:26" */

      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",

               tm);

      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);

      if(result)

