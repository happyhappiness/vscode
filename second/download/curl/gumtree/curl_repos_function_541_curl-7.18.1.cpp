ssize_t Curl_scp_send(struct connectdata *conn, int sockindex,
                      void *mem, size_t len)
{
  ssize_t nwrite;
  (void)sockindex; /* we only support SCP on the fixed known primary socket */

  /* libssh2_channel_write() returns int! */
  nwrite = (ssize_t)
    libssh2_channel_write(conn->proto.sshc.ssh_channel, mem, len);
  if(nwrite == LIBSSH2_ERROR_EAGAIN)
    return 0;

  return nwrite;
}