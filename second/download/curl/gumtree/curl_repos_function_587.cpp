int
Curl_sec_fflush_fd(struct connectdata *conn, int fd)
{
  if(conn->data_prot != prot_clear) {
    if(conn->out_buffer.index > 0){
      Curl_sec_write(conn, fd,
                conn->out_buffer.data, conn->out_buffer.index);
      conn->out_buffer.index = 0;
    }
    sec_send(conn, fd, NULL, 0);
  }
  return 0;
}