static int
sec_send(struct connectdata *conn, int fd, char *from, int length)
{
  int bytes;
  void *buf;
  bytes = (conn->mech->encode)(conn->app_data, from, length, conn->data_prot,
                               &buf, conn);
  bytes = htonl(bytes);
  block_write(fd, &bytes, sizeof(bytes));
  block_write(fd, buf, ntohl(bytes));
  free(buf);
  return length;
}