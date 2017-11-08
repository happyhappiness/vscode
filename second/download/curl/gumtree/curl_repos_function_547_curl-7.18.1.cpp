ssize_t Curl_sftp_send(struct connectdata *conn, int sockindex,
                       void *mem, size_t len)
{
  ssize_t nwrite;   /* libssh2_sftp_write() used to return size_t in 0.14
                       but is changed to ssize_t in 0.15. These days we don't
                       support libssh2 0.15*/
  (void)sockindex;

  nwrite = libssh2_sftp_write(conn->proto.sshc.sftp_handle, mem, len);
  if(nwrite == LIBSSH2_ERROR_EAGAIN)
    return 0;

  return nwrite;
}