int
Curl_sec_login(struct connectdata *conn)
{
  int ret;
  struct Curl_sec_client_mech **m;
  ssize_t nread;
  struct SessionHandle *data=conn->data;

  for(m = mechs; *m && (*m)->name; m++) {
    void *tmp;

    tmp = realloc(conn->app_data, (*m)->size);
    if (tmp == NULL) {
      failf (data, "realloc %u failed", (*m)->size);
      return -1;
    }
    conn->app_data = tmp;
	    
    if((*m)->init && (*(*m)->init)(conn->app_data) != 0) {
      infof(data, "Skipping %s...\n", (*m)->name);
      continue;
    }
    infof(data, "Trying %s...\n", (*m)->name);
    /*ret = command("AUTH %s", (*m)->name);***/
    Curl_ftpsendf(conn->firstsocket, conn,
                  "AUTH %s", (*m)->name);
    /* wait for feedback */
    nread = Curl_GetFTPResponse(conn->firstsocket,
                                conn->data->state.buffer, conn, NULL);
    if(nread < 0)
      return /*CURLE_OPERATION_TIMEOUTED*/-1;
    if(/*ret != CONTINUE*/conn->data->state.buffer[0] != '3'){
      if(/*code == 504*/strncmp(conn->data->state.buffer,"504",3) == 0) {
        infof(data,
              "%s is not supported by the server.\n", (*m)->name);
      }
      else if(/*code == 534*/strncmp(conn->data->state.buffer,"534",3) == 0) {
        infof(data, "%s rejected as security mechanism.\n", (*m)->name);
      }
      else if(/*ret == ERROR*/conn->data->state.buffer[0] == '5') {
        infof(data, "The server doesn't support the FTP "
              "security extensions.\n");
        return -1;
      }
      continue;
    }

    ret = (*(*m)->auth)(conn->app_data, /*host***/conn);
	
    if(ret == AUTH_CONTINUE)
      continue;
    else if(ret != AUTH_OK){
      /* mechanism is supposed to output error string */
      return -1;
    }
    conn->mech = *m;
    conn->sec_complete = 1;
    conn->command_prot = prot_safe;
    break;
  }
    
  return *m == NULL;
}