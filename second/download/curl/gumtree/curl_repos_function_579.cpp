int
Curl_sec_getc(struct connectdata *conn, FILE *F)
{
  if(conn->sec_complete && conn->data_prot) {
    char c;
    if(Curl_sec_read(conn, fileno(F), &c, 1) <= 0)
      return EOF;
    return c;
  }
  else
    return getc(F);
}