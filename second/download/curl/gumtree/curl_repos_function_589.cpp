int
Curl_sec_putc(struct connectdata *conn, int c, FILE *F)
{
  char ch = c;
  if(conn->data_prot == prot_clear)
    return putc(c, F);

  buffer_write(&conn->out_buffer, &ch, 1);
  if(c == '\n' || conn->out_buffer.index >= 1024 /* XXX */) {
    Curl_sec_write(conn, fileno(F), conn->out_buffer.data,
                   conn->out_buffer.index);
    conn->out_buffer.index = 0;
  }
  return c;
}