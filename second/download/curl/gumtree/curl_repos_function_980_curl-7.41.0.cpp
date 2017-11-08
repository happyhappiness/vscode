CURLcode Curl_rtsp_parseheader(struct connectdata *conn,
                               char *header)
{
  struct SessionHandle *data = conn->data;
  long CSeq = 0;

  if(checkprefix("CSeq:", header)) {
    /* Store the received CSeq. Match is verified in rtsp_done */
    int nc = sscanf(&header[4], ": %ld", &CSeq);
    if(nc == 1) {
      struct RTSP *rtsp = data->req.protop;
      rtsp->CSeq_recv = CSeq; /* mark the request */
      data->state.rtsp_CSeq_recv = CSeq; /* update the handle */
    }
    else {
      failf(data, "Unable to read the CSeq header: [%s]", header);
      return CURLE_RTSP_CSEQ_ERROR;
    }
  }
  else if(checkprefix("Session:", header)) {
    char *start;

    /* Find the first non-space letter */
    start = header + 8;
    while(*start && ISSPACE(*start))
      start++;

    if(!*start) {
      failf(data, "Got a blank Session ID");
    }
    else if(data->set.str[STRING_RTSP_SESSION_ID]) {
      /* If the Session ID is set, then compare */
      if(strncmp(start, data->set.str[STRING_RTSP_SESSION_ID],
                 strlen(data->set.str[STRING_RTSP_SESSION_ID]))  != 0) {
        failf(data, "Got RTSP Session ID Line [%s], but wanted ID [%s]",
              start, data->set.str[STRING_RTSP_SESSION_ID]);
        return CURLE_RTSP_SESSION_ERROR;
      }
    }
    else {
      /* If the Session ID is not set, and we find it in a response, then
         set it */

      /* The session ID can be an alphanumeric or a 'safe' character
       *
       * RFC 2326 15.1 Base Syntax:
       * safe =  "\$" | "-" | "_" | "." | "+"
       * */
      char *end = start;
      while(*end &&
            (ISALNUM(*end) || *end == '-' || *end == '_' || *end == '.' ||
             *end == '+' ||
             (*end == '\\' && *(end + 1) && *(end + 1) == '$' && (++end, 1))))
        end++;

      /* Copy the id substring into a new buffer */
      data->set.str[STRING_RTSP_SESSION_ID] = malloc(end - start + 1);
      if(data->set.str[STRING_RTSP_SESSION_ID] == NULL)
        return CURLE_OUT_OF_MEMORY;
      memcpy(data->set.str[STRING_RTSP_SESSION_ID], start, end - start);
      (data->set.str[STRING_RTSP_SESSION_ID])[end - start] = '\0';
    }
  }
  return CURLE_OK;
}