static CURLcode ntlm_wb_init(struct connectdata *conn, const char *userp)
{
  curl_socket_t sockfds[2];
  pid_t child_pid;
  const char *username;
  char *slash, *domain = NULL;
  const char *ntlm_auth = NULL;
  char *ntlm_auth_alloc = NULL;
  int error;

  /* Return if communication with ntlm_auth already set up */
  if(conn->ntlm_auth_hlpr_socket != CURL_SOCKET_BAD ||
     conn->ntlm_auth_hlpr_pid)
    return CURLE_OK;

  username = userp;
  slash = strpbrk(username, "\\/");
  if(slash) {
    if((domain = strdup(username)) == NULL)
      return CURLE_OUT_OF_MEMORY;
    slash = domain + (slash - username);
    *slash = '\0';
    username = username + (slash - domain) + 1;
  }

  /* For testing purposes, when DEBUGBUILD is defined and environment
     variable CURL_NTLM_WB_FILE is set a fake_ntlm is used to perform
     NTLM challenge/response which only accepts commands and output
     strings pre-written in test case definitions */
#ifdef DEBUGBUILD
  ntlm_auth_alloc = curl_getenv("CURL_NTLM_WB_FILE");
  if(ntlm_auth_alloc)
    ntlm_auth = ntlm_auth_alloc;
  else
#endif
    ntlm_auth = NTLM_WB_FILE;

  if(access(ntlm_auth, X_OK) != 0) {
    error = ERRNO;
    failf(conn->data, "Could not access ntlm_auth: %s errno %d: %s",
          ntlm_auth, error, Curl_strerror(conn, error));
    goto done;
  }

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds)) {
    error = ERRNO;
    failf(conn->data, "Could not open socket pair. errno %d: %s",
          error, Curl_strerror(conn, error));
    goto done;
  }

  child_pid = fork();
  if(child_pid == -1) {
    error = ERRNO;
    sclose(sockfds[0]);
    sclose(sockfds[1]);
    failf(conn->data, "Could not fork. errno %d: %s",
          error, Curl_strerror(conn, error));
    goto done;
  }
  else if(!child_pid) {
    /*
     * child process
     */

    /* Don't use sclose in the child since it fools the socket leak detector */
    sclose_nolog(sockfds[0]);
    if(dup2(sockfds[1], STDIN_FILENO) == -1) {
      error = ERRNO;
      failf(conn->data, "Could not redirect child stdin. errno %d: %s",
            error, Curl_strerror(conn, error));
      exit(1);
    }

    if(dup2(sockfds[1], STDOUT_FILENO) == -1) {
      error = ERRNO;
      failf(conn->data, "Could not redirect child stdout. errno %d: %s",
            error, Curl_strerror(conn, error));
      exit(1);
    }

    if(domain)
      execl(ntlm_auth, ntlm_auth,
            "--helper-protocol", "ntlmssp-client-1",
            "--use-cached-creds",
            "--username", username,
            "--domain", domain,
            NULL);
    else
      execl(ntlm_auth, ntlm_auth,
            "--helper-protocol", "ntlmssp-client-1",
            "--use-cached-creds",
            "--username", username,
            NULL);

    error = ERRNO;
    sclose_nolog(sockfds[1]);
    failf(conn->data, "Could not execl(). errno %d: %s",
          error, Curl_strerror(conn, error));
    exit(1);
  }

  sclose(sockfds[1]);
  conn->ntlm_auth_hlpr_socket = sockfds[0];
  conn->ntlm_auth_hlpr_pid = child_pid;
  Curl_safefree(domain);
  Curl_safefree(ntlm_auth_alloc);
  return CURLE_OK;

done:
  Curl_safefree(domain);
  Curl_safefree(ntlm_auth_alloc);
  return CURLE_REMOTE_ACCESS_DENIED;
}