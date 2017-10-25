static CURLcode ftp_range(struct connectdata *conn)
{
  curl_off_t from, to;
  curl_off_t totalsize=-1;
  char *ptr;
  char *ptr2;
  struct FTP *ftp = conn->proto.ftp;

  if(conn->bits.use_range && conn->range) {
    from=curlx_strtoofft(conn->range, &ptr, 0);
    while(ptr && *ptr && (isspace((int)*ptr) || (*ptr=='-')))
      ptr++;
    to=curlx_strtoofft(ptr, &ptr2, 0);
    if(ptr == ptr2) {
      /* we didn't get any digit */
      to=-1;
    }
    if((-1 == to) && (from>=0)) {
      /* X - */
      conn->resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE %" FORMAT_OFF_T " to end of file\n",
                   from));
    }
    else if(from < 0) {
      /* -Y */
      totalsize = -from;
      conn->maxdownload = -from;
      conn->resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE the last %" FORMAT_OFF_T " bytes\n",
                   totalsize));
    }
    else {
      /* X-Y */
      totalsize = to-from;
      conn->maxdownload = totalsize+1; /* include the last mentioned byte */
      conn->resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE from %" FORMAT_OFF_T
                   " getting %" FORMAT_OFF_T " bytes\n",
                   from, conn->maxdownload));
    }
    DEBUGF(infof(conn->data, "range-download from %" FORMAT_OFF_T
                 " to %" FORMAT_OFF_T ", totally %" FORMAT_OFF_T " bytes\n",
                 from, to, conn->maxdownload));
    ftp->dont_check = TRUE; /* dont check for successful transfer */
  }
  return CURLE_OK;
}