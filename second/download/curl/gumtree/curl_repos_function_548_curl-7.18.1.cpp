ssize_t Curl_sftp_recv(struct connectdata *conn, int sockindex,
                       char *mem, size_t len)
{
  ssize_t nread;
  (void)sockindex;

  nread = libssh2_sftp_read(conn->proto.sshc.sftp_handle, mem, len);

  return nread;
}