static CURLcode ftp_range(struct connectdata *conn)
{
  curl_off_t from, to;
  curl_off_t totalsize=-1;
  char *ptr;
  char *ptr2;
  struct SessionHandle *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(data->state.use_range && data->state.range) {
    from=curlx_strtoofft(data->state.range, &ptr, 0);
    while(ptr && *ptr && (ISSPACE(*ptr) || (*ptr=='-')))
      ptr++;
    to=curlx_strtoofft(ptr, &ptr2, 0);
    if(ptr == ptr2) {
      /* we didn't get any digit */
      to=-1;
    }
    if((-1 == to) && (from>=0)) {
      /* X - */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE %" FORMAT_OFF_T " to end of file\n",
                   from));
    }
    else if(from < 0) {
      /* -Y */
      totalsize = -from;
      data->req.maxdownload = -from;
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE the last %" FORMAT_OFF_T " bytes\n",
                   totalsize));
    }
    else {
      /* X-Y */
      totalsize = to-from;
      data->req.maxdownload = totalsize+1; /* include last byte */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE from %" FORMAT_OFF_T
                   " getting %" FORMAT_OFF_T " bytes\n",
                   from, data->req.maxdownload));
    }
    DEBUGF(infof(conn->data, "range-download from %" FORMAT_OFF_T
                 " to %" FORMAT_OFF_T ", totally %" FORMAT_OFF_T " bytes\n",
                 from, to, data->req.maxdownload));
    ftpc->dont_check = TRUE; /* dont check for successful transfer */
  }
  else
    data->req.maxdownload = -1;
  return CURLE_OK;
}