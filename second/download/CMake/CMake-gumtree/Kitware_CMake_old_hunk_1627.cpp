{

  ssize_t bytes_written;

  char s[256];

  ssize_t write_len;

  char *sptr=s;

  CURLcode res = CURLE_OK;



  va_list ap;

  va_start(ap, fmt);

  vsnprintf(s, 250, fmt, ap);

  va_end(ap);

  

  strcat(s, "\r\n"); /* append a trailing CRLF */



  bytes_written=0;

  write_len = (int)strlen(s);



  do {

    res = Curl_write(conn, conn->firstsocket, sptr, write_len,

                     &bytes_written);



    if(CURLE_OK != res)

      break;



    if(conn->data->set.verbose)

      Curl_debug(conn->data, CURLINFO_HEADER_OUT, sptr, bytes_written);



    if(bytes_written != write_len) {

      write_len -= bytes_written;

      sptr += bytes_written;

    }

    else

      break;

  } while(1);



  return res;

}



/***********************************************************************

 *

 * Curl_ftp_disconnect()

 *

 * Disconnect from an FTP server. Cleanup protocol-specific per-connection

