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
    int code;
    if(Curl_ftpsendf(conn, "PBSZ %u", s))
      return -1;

    if(Curl_GetFTPResponse(&nread, conn, &code))
      return -1;

    if(code/100 != '2'){
      failf(conn->data, "Failed to set protection buffer size.");
      return -1;
    }
    conn->buffer_size = s;

    p = strstr(conn->data->state.buffer, "PBSZ=");
    if(p)
      sscanf(p, "PBSZ=%u", &s);
    if(s < conn->buffer_size)
      conn->buffer_size = s;
  }

  if(Curl_ftpsendf(conn, "PROT %c", level["CSEP"]))
    return -1;

  if(Curl_GetFTPResponse(&nread, conn, NULL))
    return -1;

  if(conn->data->state.buffer[0] != '2'){
    failf(conn->data, "Failed to set protection level.");
    return -1;
  }

  conn->data_prot = (enum protection_level)level;
  return 0;
}