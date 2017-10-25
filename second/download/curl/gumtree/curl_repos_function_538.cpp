static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
                                    int ftpcode)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data=conn->data;

  switch(ftpcode) {
  case 213:
    {
      /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the
         last .sss part is optional and means fractions of a second */
      int year, month, day, hour, minute, second;
      char *buf = data->state.buffer;
      if(6 == sscanf(buf+4, "%04d%02d%02d%02d%02d%02d",
                     &year, &month, &day, &hour, &minute, &second)) {
        /* we have a time, reformat it */
        time_t secs=time(NULL);
        /* using the good old yacc/bison yuck */
        snprintf(buf, sizeof(conn->data->state.buffer),
                 "%04d%02d%02d %02d:%02d:%02d GMT",
                 year, month, day, hour, minute, second);
        /* now, convert this into a time() value: */
        data->info.filetime = (long)curl_getdate(buf, &secs);
      }

      /* If we asked for a time of the file and we actually got one as well,
         we "emulate" a HTTP-style header in our output. */

      if(conn->bits.no_body &&
         data->set.include_header &&
         ftp->file &&
         data->set.get_filetime &&
         (data->info.filetime>=0) ) {
        struct tm *tm;
        time_t clock = (time_t)data->info.filetime;
#ifdef HAVE_GMTIME_R
        struct tm buffer;
        tm = (struct tm *)gmtime_r(&clock, &buffer);
#else
        tm = gmtime(&clock);
#endif
        /* format: "Tue, 15 Nov 1994 12:45:26" */
        snprintf(buf, BUFSIZE-1,
                 "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
                 Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
                 tm->tm_mday,
                 Curl_month[tm->tm_mon],
                 tm->tm_year + 1900,
                 tm->tm_hour,
                 tm->tm_min,
                 tm->tm_sec);
        result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
        if(result)
          return result;
      } /* end of a ridiculous amount of conditionals */
    }
    break;
  default:
    infof(data, "unsupported MDTM reply format\n");
    break;
  case 550: /* "No such file or directory" */
    failf(data, "Given file does not exist");
    result = CURLE_FTP_COULDNT_RETR_FILE;
    break;
  }

  if(data->set.timecondition) {
    if((data->info.filetime > 0) && (data->set.timevalue > 0)) {
      switch(data->set.timecondition) {
      case CURL_TIMECOND_IFMODSINCE:
      default:
        if(data->info.filetime < data->set.timevalue) {
          infof(data, "The requested document is not new enough\n");
          ftp->no_transfer = TRUE; /* mark this to not transfer data */
          state(conn, FTP_STOP);
          return CURLE_OK;
        }
        break;
      case CURL_TIMECOND_IFUNMODSINCE:
        if(data->info.filetime > data->set.timevalue) {
          infof(data, "The requested document is not old enough\n");
          ftp->no_transfer = TRUE; /* mark this to not transfer data */
          state(conn, FTP_STOP);
          return CURLE_OK;
        }
        break;
      } /* switch */
    }
    else {
      infof(data, "Skipping time comparison\n");
    }
  }

  if(!result)
    result = ftp_state_post_mdtm(conn);

  return result;
}