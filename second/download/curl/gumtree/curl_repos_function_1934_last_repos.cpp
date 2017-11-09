static CURLcode ftp_range(struct connectdata *conn)
{
  curl_off_t from, to;
  char *ptr;
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(data->state.use_range && data->state.range) {
    CURLofft from_t;
    CURLofft to_t;
    from_t = curlx_strtoofft(data->state.range, &ptr, 0, &from);
    if(from_t == CURL_OFFT_FLOW)
      return CURLE_RANGE_ERROR;
    while(*ptr && (ISSPACE(*ptr) || (*ptr == '-')))
      ptr++;
    to_t = curlx_strtoofft(ptr, NULL, 0, &to);
    if(to_t == CURL_OFFT_FLOW)
      return CURLE_RANGE_ERROR;
    if((to_t == CURL_OFFT_INVAL) && !from_t) {
      /* X - */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE %" CURL_FORMAT_CURL_OFF_T
                   " to end of file\n", from));
    }
    else if(!to_t && (from_t == CURL_OFFT_INVAL)) {
      /* -Y */
      data->req.maxdownload = to;
      data->state.resume_from = -to;
      DEBUGF(infof(conn->data, "FTP RANGE the last %" CURL_FORMAT_CURL_OFF_T
                   " bytes\n", to));
    }
    else {
      /* X-Y */
      data->req.maxdownload = (to - from) + 1; /* include last byte */
      data->state.resume_from = from;
      DEBUGF(infof(conn->data, "FTP RANGE from %" CURL_FORMAT_CURL_OFF_T
                   " getting %" CURL_FORMAT_CURL_OFF_T " bytes\n",
                   from, data->req.maxdownload));
    }
    DEBUGF(infof(conn->data, "range-download from %" CURL_FORMAT_CURL_OFF_T
                 " to %" CURL_FORMAT_CURL_OFF_T ", totally %"
                 CURL_FORMAT_CURL_OFF_T " bytes\n",
                 from, to, data->req.maxdownload));
    ftpc->dont_check = TRUE; /* don't check for successful transfer */
  }
  else
    data->req.maxdownload = -1;
  return CURLE_OK;
}