static ssize_t scp_send(struct connectdata *conn, int sockindex,
                        const void *mem, size_t len, CURLcode *err)
{
  ssize_t nwrite;
  (void)sockindex; /* we only support SCP on the fixed known primary socket */

  /* libssh2_channel_write() returns int! */
  nwrite = (ssize_t)
    libssh2_channel_write(conn->proto.sshc.ssh_channel, mem, len);

  ssh_block2waitfor(conn, (nwrite == LIBSSH2_ERROR_EAGAIN)?TRUE:FALSE);

  if(nwrite == LIBSSH2_ERROR_EAGAIN) {
    *err = CURLE_AGAIN;
    nwrite = 0;
  }
  else if(nwrite < LIBSSH2_ERROR_NONE) {
    *err = libssh2_session_error_to_CURLE((int)nwrite);
    nwrite = -1;
  }

  return nwrite;
}