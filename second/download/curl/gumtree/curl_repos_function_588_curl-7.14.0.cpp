int
Curl_sec_write(struct connectdata *conn, int fd, char *buffer, int length)
{
  int len = conn->buffer_size;
  int tx = 0;

  if(conn->data_prot == prot_clear)
    return write(fd, buffer, length);

  len -= (conn->mech->overhead)(conn->app_data, conn->data_prot, len);
  while(length){
    if(length < len)
      len = length;
    sec_send(conn, fd, buffer, len);
    length -= len;
    buffer += len;
    tx += len;
  }
  return tx;
}