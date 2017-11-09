static CURLcode ntlm_wb_response(struct connectdata *conn,
                                 const char *input, curlntlm state)
{
  char *buf = malloc(NTLM_BUFSIZE);
  size_t len_in = strlen(input), len_out = 0;

  if(!buf)
    return CURLE_OUT_OF_MEMORY;

  while(len_in > 0) {
    ssize_t written = swrite(conn->ntlm_auth_hlpr_socket, input, len_in);
    if(written == -1) {
      /* Interrupted by a signal, retry it */
      if(errno == EINTR)
        continue;
      /* write failed if other errors happen */
      goto done;
    }
    input += written;
    len_in -= written;
  }
  /* Read one line */
  while(1) {
    ssize_t size;
    char *newbuf;

    size = sread(conn->ntlm_auth_hlpr_socket, buf + len_out, NTLM_BUFSIZE);
    if(size == -1) {
      if(errno == EINTR)
        continue;
      goto done;
    }
    else if(size == 0)
      goto done;

    len_out += size;
    if(buf[len_out - 1] == '\n') {
      buf[len_out - 1] = '\0';
      break;
    }
    newbuf = Curl_saferealloc(buf, len_out + NTLM_BUFSIZE);
    if(!newbuf)
      return CURLE_OUT_OF_MEMORY;

    buf = newbuf;
  }

  /* Samba/winbind installed but not configured */
  if(state == NTLMSTATE_TYPE1 &&
     len_out == 3 &&
     buf[0] == 'P' && buf[1] == 'W')
    goto done;
  /* invalid response */
  if(len_out < 4)
    goto done;
  if(state == NTLMSTATE_TYPE1 &&
     (buf[0]!='Y' || buf[1]!='R' || buf[2]!=' '))
    goto done;
  if(state == NTLMSTATE_TYPE2 &&
     (buf[0]!='K' || buf[1]!='K' || buf[2]!=' ') &&
     (buf[0]!='A' || buf[1]!='F' || buf[2]!=' '))
    goto done;

  conn->response_header = aprintf("NTLM %.*s", len_out - 4, buf + 3);
  free(buf);
  return CURLE_OK;
done:
  free(buf);
  return CURLE_REMOTE_ACCESS_DENIED;
}