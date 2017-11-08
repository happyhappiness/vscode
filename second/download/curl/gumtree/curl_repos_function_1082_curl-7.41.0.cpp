static ssize_t sftp_recv(struct connectdata *conn, int sockindex,
                         char *mem, size_t len, CURLcode *err)
{
  ssize_t nread;
  (void)sockindex;

  nread = libssh2_sftp_read(conn->proto.sshc.sftp_handle, mem, len);

  ssh_block2waitfor(conn, (nread == LIBSSH2_ERROR_EAGAIN)?TRUE:FALSE);

  if(nread == LIBSSH2_ERROR_EAGAIN) {
    *err = CURLE_AGAIN;
    nread = -1;

  }
  else if(nread < 0) {
    *err = libssh2_session_error_to_CURLE((int)nread);
  }
  return nread;
}