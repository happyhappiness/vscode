static CURLcode ftp_range(struct connectdata *conn)
{
  curl_off_t from, to;
  char *ptr;
  char *ptr2;
  struct SessionHandle *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(data->state.use_range && data->state.range) {
    from=curlx_strtoofft(data->state.range, &ptr, 0);
    while(*ptr && (ISSPACE(*ptr) || (*ptr=='-')))
      ptr++;
    to=curlx_strtoofft(ptr, &ptr2, 0);
    if(ptr == ptr2) {
      /* we didn't get any digit */
      to=-1;
    }
    if((-1 == to) && (from>=0)) {
      /* X - */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE %" CURL_FORMAT_CURL_OFF_T
                   " to end of file\n", from));
    }
    else if(from < 0) {
      /* -Y */
      data->req.maxdownload = -from;
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE the last %" CURL_FORMAT_CURL_OFF_T
                   " bytes\n", -from));
    }
    else {
      /* X-Y */
      data->req.maxdownload = (to-from)+1; /* include last byte */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE from %" CURL_FORMAT_CURL_OFF_T
                   " getting %" CURL_FORMAT_CURL_OFF_T " bytes\n",
                   from, data->req.maxdownload));
    }
    DEBUGF(infof(conn->data, "range-download from %" CURL_FORMAT_CURL_OFF_T
                 " to %" CURL_FORMAT_CURL_OFF_T ", totally %"
                 CURL_FORMAT_CURL_OFF_T " bytes\n",
                 from, to, data->req.maxdownload));
    ftpc->dont_check = TRUE; /* dont check for successful transfer */
  }
  else
    data->req.maxdownload = -1;
  return CURLE_OK;
}