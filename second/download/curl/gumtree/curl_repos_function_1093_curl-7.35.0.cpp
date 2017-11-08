static CURLcode ntlm_wb_response(struct connectdata *conn,
                                 const char *input, curlntlm state)
{
  ssize_t size;
  char buf[200]; /* enough, type 1, 3 message length is less then 200 */
  char *tmpbuf = buf;
  size_t len_in = strlen(input), len_out = sizeof(buf);

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
  while(len_out > 0) {
    size = sread(conn->ntlm_auth_hlpr_socket, tmpbuf, len_out);
    if(size == -1) {
      if(errno == EINTR)
        continue;
      goto done;
    }
    else if(size == 0)
      goto done;
    else if(tmpbuf[size - 1] == '\n') {
      tmpbuf[size - 1] = '\0';
      goto wrfinish;
    }
    tmpbuf += size;
    len_out -= size;
  }
  goto done;
wrfinish:
  /* Samba/winbind installed but not configured */
  if(state == NTLMSTATE_TYPE1 &&
     size == 3 &&
     buf[0] == 'P' && buf[1] == 'W')
    return CURLE_REMOTE_ACCESS_DENIED;
  /* invalid response */
  if(size < 4)
    goto done;
  if(state == NTLMSTATE_TYPE1 &&
     (buf[0]!='Y' || buf[1]!='R' || buf[2]!=' '))
    goto done;
  if(state == NTLMSTATE_TYPE2 &&
     (buf[0]!='K' || buf[1]!='K' || buf[2]!=' ') &&
     (buf[0]!='A' || buf[1]!='F' || buf[2]!=' '))
    goto done;

  conn->response_header = aprintf("NTLM %.*s", size - 4, buf + 3);
  return CURLE_OK;
done:
  return CURLE_REMOTE_ACCESS_DENIED;
}