CURLcode Curl_output_ntlm_wb(struct connectdata *conn,
                              bool proxy)
{
  /* point to the address of the pointer that holds the string to send to the
     server, which is for a plain host or for a HTTP proxy */
  char **allocuserpwd;
  /* point to the name and password for this */
  const char *userp;
  /* point to the correct struct with this */
  struct ntlmdata *ntlm;
  struct auth *authp;

  CURLcode res = CURLE_OK;
  char *input;

  DEBUGASSERT(conn);
  DEBUGASSERT(conn->data);

  if(proxy) {
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->http_proxy.user;
    ntlm = &conn->proxyntlm;
    authp = &conn->data->state.authproxy;
  }
  else {
    allocuserpwd = &conn->allocptr.userpwd;
    userp = conn->user;
    ntlm = &conn->ntlm;
    authp = &conn->data->state.authhost;
  }
  authp->done = FALSE;

  /* not set means empty */
  if(!userp)
    userp = "";

  switch(ntlm->state) {
  case NTLMSTATE_TYPE1:
  default:
    /* Use Samba's 'winbind' daemon to support NTLM authentication,
     * by delegating the NTLM challenge/response protocal to a helper
     * in ntlm_auth.
     * http://devel.squid-cache.org/ntlm/squid_helper_protocol.html
     * https://www.samba.org/samba/docs/man/manpages-3/winbindd.8.html
     * https://www.samba.org/samba/docs/man/manpages-3/ntlm_auth.1.html
     * Preprocessor symbol 'NTLM_WB_ENABLED' is defined when this
     * feature is enabled and 'NTLM_WB_FILE' symbol holds absolute
     * filename of ntlm_auth helper.
     * If NTLM authentication using winbind fails, go back to original
     * request handling process.
     */
    /* Create communication with ntlm_auth */
    res = ntlm_wb_init(conn, userp);
    if(res)
      return res;
    res = ntlm_wb_response(conn, "YR\n", ntlm->state);
    if(res)
      return res;

    free(*allocuserpwd);
    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                            proxy ? "Proxy-" : "",
                            conn->response_header);
    DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
    free(conn->response_header);
    conn->response_header = NULL;
    break;
  case NTLMSTATE_TYPE2:
    input = aprintf("TT %s\n", conn->challenge_header);
    if(!input)
      return CURLE_OUT_OF_MEMORY;
    res = ntlm_wb_response(conn, input, ntlm->state);
    free(input);
    input = NULL;
    if(res)
      return res;

    free(*allocuserpwd);
    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                            proxy ? "Proxy-" : "",
                            conn->response_header);
    DEBUG_OUT(fprintf(stderr, "**** %s\n ", *allocuserpwd));
    ntlm->state = NTLMSTATE_TYPE3; /* we sent a type-3 */
    authp->done = TRUE;
    Curl_ntlm_wb_cleanup(conn);
    break;
  case NTLMSTATE_TYPE3:
    /* connection is already authenticated,
     * don't send a header in future requests */
    free(*allocuserpwd);
    *allocuserpwd = NULL;
    authp->done = TRUE;
    break;
  }

  return CURLE_OK;
}