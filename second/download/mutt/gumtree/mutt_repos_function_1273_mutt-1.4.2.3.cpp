static void flush_buffer(char *buf, size_t *len, CONNECTION *conn)
{
  buf[*len] = '\0';
  mutt_socket_write(conn, buf);
  *len = 0;
}