static int data_pending(const struct connectdata *conn)
{
  /* in the case of libssh2, we can never be really sure that we have emptied
     its internal buffers so we MUST always try until we get EAGAIN back */
  return conn->protocol&(PROT_SCP|PROT_SFTP) ||
    Curl_ssl_data_pending(conn, FIRSTSOCKET);
}