int
Curl_sec_read_msg(struct connectdata *conn, char *s, int level)
{
  int len;
  unsigned char *buf;
  int code;

  len = Curl_base64_decode(s + 4, &buf); /* XXX */
  if(len > 0)
    len = (conn->mech->decode)(conn->app_data, buf, len, level, conn);
  else
    return -1;

  if(len < 0) {
    free(buf);
    return -1;
  }

  buf[len] = '\0';

  if(buf[3] == '-')
    code = 0;
  else
    sscanf((char *)buf, "%d", &code);
  if(buf[len-1] == '\n')
    buf[len-1] = '\0';
  strcpy(s, (char *)buf);
  free(buf);
  return code;
}