ssize_t Curl_scp_recv(struct connectdata *conn, int sockindex,
                      char *mem, size_t len)
{
  ssize_t nread;
  (void)sockindex; /* we only support SCP on the fixed known primary socket */

  /* libssh2_channel_read() returns int */
  nread = (ssize_t)
    libssh2_channel_read(conn->proto.sshc.ssh_channel, mem, len);
  return nread;
}