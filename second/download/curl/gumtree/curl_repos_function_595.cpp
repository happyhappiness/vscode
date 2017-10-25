int
Curl_sec_login(struct connectdata *conn)
{
  int ret;
  const struct Curl_sec_client_mech * const *m;
  ssize_t nread;
  struct SessionHandle *data=conn->data;
  int ftpcode;

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

    if(Curl_ftpsendf(conn, "AUTH %s", (*m)->name))
      return -1;

    if(Curl_GetFTPResponse(&nread, conn, &ftpcode))
      return -1;

    if(conn->data->state.buffer[0] != '3'){
      switch(ftpcode) {
      case 504:
        infof(data,
              "%s is not supported by the server.\n", (*m)->name);
        break;
      case 534:
        infof(data, "%s rejected as security mechanism.\n", (*m)->name);
        break;
      default:
        if(conn->data->state.buffer[0] == '5') {
          infof(data, "The server doesn't support the FTP "
                "security extensions.\n");
          return -1;
        }
        break;
      }
      continue;
    }

    ret = (*(*m)->auth)(conn->app_data, conn);

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