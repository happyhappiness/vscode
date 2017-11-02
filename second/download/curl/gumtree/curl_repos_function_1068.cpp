static CURLcode ssh_connect(struct connectdata *conn, bool *done)
{
#ifdef CURL_LIBSSH2_DEBUG
  curl_socket_t sock;
#endif
  struct ssh_conn *ssh;
  CURLcode result;
  struct SessionHandle *data = conn->data;

  /* initialize per-handle data if not already */
  if(!data->req.protop)
    ssh_setup_connection(conn);

  /* We default to persistent connections. We set this already in this connect
     function to make the re-use checks properly be able to check this bit. */
  connkeep(conn, "SSH default");

  if(conn->handler->protocol & CURLPROTO_SCP) {
    conn->recv[FIRSTSOCKET] = scp_recv;
    conn->send[FIRSTSOCKET] = scp_send;
  }
  else {
    conn->recv[FIRSTSOCKET] = sftp_recv;
    conn->send[FIRSTSOCKET] = sftp_send;
  }
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

  ssh->ssh_session = libssh2_session_init_ex(my_libssh2_malloc,
                                             my_libssh2_free,
                                             my_libssh2_realloc, conn);
  if(ssh->ssh_session == NULL) {
    failf(data, "Failure initialising ssh session");
    return CURLE_FAILED_INIT;
  }

#ifdef HAVE_LIBSSH2_KNOWNHOST_API
  if(data->set.str[STRING_SSH_KNOWNHOSTS]) {
    int rc;
    ssh->kh = libssh2_knownhost_init(ssh->ssh_session);
    if(!ssh->kh) {
      /* eeek. TODO: free the ssh_session! */
      return CURLE_FAILED_INIT;
    }

    /* read all known hosts from there */
    rc = libssh2_knownhost_readfile(ssh->kh,
                                    data->set.str[STRING_SSH_KNOWNHOSTS],
                                    LIBSSH2_KNOWNHOST_FILE_OPENSSH);
    if(rc < 0)
      infof(data, "Failed to read known hosts from %s\n",
            data->set.str[STRING_SSH_KNOWNHOSTS]);
  }
#endif /* HAVE_LIBSSH2_KNOWNHOST_API */

#ifdef CURL_LIBSSH2_DEBUG
  libssh2_trace(ssh->ssh_session, ~0);
  infof(data, "SSH socket: %d\n", (int)sock);
#endif /* CURL_LIBSSH2_DEBUG */

  state(conn, SSH_INIT);

  result = ssh_multi_statemach(conn, done);

  return result;
}