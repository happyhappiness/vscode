static int
sec_prot_internal(struct connectdata *conn, int level)
{
  char *p;
  unsigned int s = 1048576;
  ssize_t nread;

  if(!conn->sec_complete){
    infof(conn->data, "No security data exchange has taken place.\n");
    return -1;
  }

  if(level){
    Curl_ftpsendf(conn->firstsocket, conn,
                  "PBSZ %u", s);
    /* wait for feedback */
    nread = Curl_GetFTPResponse(conn->firstsocket,
                                conn->data->state.buffer, conn, NULL);
    if(nread < 0)
      return /*CURLE_OPERATION_TIMEOUTED*/-1;
    if(/*ret != COMPLETE*/conn->data->state.buffer[0] != '2'){
      failf(conn->data, "Failed to set protection buffer size.\n");
      return -1;
    }
    conn->buffer_size = s;
    p = strstr(/*reply_string*/conn->data->state.buffer, "PBSZ=");
    if(p)
      sscanf(p, "PBSZ=%u", &s);
    if(s < conn->buffer_size)
      conn->buffer_size = s;
  }

  Curl_ftpsendf(conn->firstsocket, conn,
                "PROT %c", level["CSEP"]);
  /* wait for feedback */
  nread = Curl_GetFTPResponse(conn->firstsocket,
                              conn->data->state.buffer, conn, NULL);
  if(nread < 0)
    return /*CURLE_OPERATION_TIMEOUTED*/-1;
  if(/*ret != COMPLETE*/conn->data->state.buffer[0] != '2'){
    failf(conn->data, "Failed to set protection level.\n");
    return -1;
  }
    
  conn->data_prot = (enum protection_level)level;
  return 0;
}