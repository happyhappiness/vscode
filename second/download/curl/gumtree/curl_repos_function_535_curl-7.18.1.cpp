static CURLcode ssh_connect(struct connectdata *conn, bool *done)
{
#ifdef CURL_LIBSSH2_DEBUG
  curl_socket_t sock;
#endif
  struct ssh_conn *ssh;
  CURLcode result;
  struct SessionHandle *data = conn->data;

  /* We default to persistent connections. We set this already in this connect
     function to make the re-use checks properly be able to check this bit. */
  conn->bits.close = FALSE;

  /* If there already is a protocol-specific struct allocated for this
     sessionhandle, deal with it */
  Curl_reset_reqproto(conn);

  result = ssh_init(conn);
  if(result)
    return result;

  ssh = &conn->proto.sshc;

#ifdef CURL_LIBSSH2_DEBUG
  if(conn->user) {
    infof(data, "User: %s\n", conn->user);
  }
  if(conn->passwd) {
    infof(data, "Password: %s\n", conn->passwd);
  }
  sock = conn->sock[FIRSTSOCKET];
#endif /* CURL_LIBSSH2_DEBUG */

  ssh->ssh_session = libssh2_session_init_ex(libssh2_malloc, libssh2_free,
                                             libssh2_realloc, conn);
  if(ssh->ssh_session == NULL) {
    failf(data, "Failure initialising ssh session");
    return CURLE_FAILED_INIT;
  }

#ifdef CURL_LIBSSH2_DEBUG
  libssh2_trace(ssh->ssh_session, LIBSSH2_TRACE_CONN|LIBSSH2_TRACE_TRANS|
                LIBSSH2_TRACE_KEX|LIBSSH2_TRACE_AUTH|LIBSSH2_TRACE_SCP|
                LIBSSH2_TRACE_SFTP|LIBSSH2_TRACE_ERROR|
                LIBSSH2_TRACE_PUBLICKEY);
  infof(data, "SSH socket: %d\n", sock);
#endif /* CURL_LIBSSH2_DEBUG */

  state(conn, SSH_S_STARTUP);

  if(data->state.used_interface == Curl_if_multi)
    result = ssh_multi_statemach(conn, done);
  else {
    result = ssh_easy_statemach(conn);
    if(!result)
      *done = TRUE;
  }

  return result;
}