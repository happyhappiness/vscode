static ssize_t scp_recv(struct connectdata *conn, int sockindex,
                        char *mem, size_t len, CURLcode *err)
{
  ssize_t nread;
  (void)sockindex; /* we only support SCP on the fixed known primary socket */

  /* libssh2_channel_read() returns int */
  nread = (ssize_t)
    libssh2_channel_read(conn->proto.sshc.ssh_channel, mem, len);

  ssh_block2waitfor(conn, (nread == LIBSSH2_ERROR_EAGAIN)?TRUE:FALSE);
  if(nread == LIBSSH2_ERROR_EAGAIN) {
    *err = CURLE_AGAIN;
    nread = -1;
  }

  return nread;
}