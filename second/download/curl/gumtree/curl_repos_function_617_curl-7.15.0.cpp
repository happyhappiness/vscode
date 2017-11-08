static int
sec_get_data(struct connectdata *conn,
             int fd, struct krb4buffer *buf)
{
  int len;
  int b;

  b = block_read(fd, &len, sizeof(len));
  if (b == 0)
    return 0;
  else if (b < 0)
    return -1;
  len = ntohl(len);
  buf->data = realloc(buf->data, len);
  b = block_read(fd, buf->data, len);
  if (b == 0)
    return 0;
  else if (b < 0)
    return -1;
  buf->size = (conn->mech->decode)(conn->app_data, buf->data, len,
                                   conn->data_prot, conn);
  buf->index = 0;
  return 0;
}