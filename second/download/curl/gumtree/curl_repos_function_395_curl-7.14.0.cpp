CURLcode Curl_http_input_auth(struct connectdata *conn,
                              int httpcode,
                              char *header) /* the first non-space */
{
  /*
   * This resource requires authentication
   */
  struct SessionHandle *data = conn->data;

  long *availp;
  char *start;
  struct auth *authp;

  if (httpcode == 407) {
    start = header+strlen("Proxy-authenticate:");
    availp = &data->info.proxyauthavail;
    authp = &data->state.authproxy;
  }
  else {
    start = header+strlen("WWW-Authenticate:");
    availp = &data->info.httpauthavail;
    authp = &data->state.authhost;
  }

  /* pass all white spaces */
  while(*start && isspace((int)*start))
    start++;

  /*
   * Here we check if we want the specific single authentiction (using ==) and
   * if we do, we initiate usage of it.
   *
   * If the provided authentication is wanted as one out of several accepted
   * types (using &), we OR this authenticaion type to the authavail
   * variable.
   */

#ifdef HAVE_GSSAPI
  if (checkprefix("GSS-Negotiate", start) ||
      checkprefix("Negotiate", start)) {
    *availp |= CURLAUTH_GSSNEGOTIATE;
    authp->avail |= CURLAUTH_GSSNEGOTIATE;
    if(authp->picked == CURLAUTH_GSSNEGOTIATE) {
      /* if exactly this is wanted, go */
      int neg = Curl_input_negotiate(conn, start);
      if (neg == 0) {
        conn->newurl = strdup(data->change.url);
        data->state.authproblem = (conn->newurl == NULL);
      }
      else {
        infof(data, "Authentication problem. Ignoring this.\n");
        data->state.authproblem = TRUE;
      }
    }
  }
  else
#endif
#ifdef USE_NTLM
    /* NTLM support requires the SSL crypto libs */
    if(checkprefix("NTLM", start)) {
      *availp |= CURLAUTH_NTLM;
      authp->avail |= CURLAUTH_NTLM;
      if(authp->picked == CURLAUTH_NTLM) {
        /* NTLM authentication is picked and activated */
        CURLntlm ntlm =
          Curl_input_ntlm(conn, (bool)(httpcode == 407), start);

        if(CURLNTLM_BAD != ntlm)
          data->state.authproblem = FALSE;
        else {
          infof(data, "Authentication problem. Ignoring this.\n");
          data->state.authproblem = TRUE;
        }
      }
    }
    else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
      if(checkprefix("Digest", start)) {
        CURLdigest dig;
        *availp |= CURLAUTH_DIGEST;
        authp->avail |= CURLAUTH_DIGEST;

        /* We call this function on input Digest headers even if Digest
         * authentication isn't activated yet, as we need to store the
         * incoming data from this header in case we are gonna use Digest. */
        dig = Curl_input_digest(conn, (bool)(httpcode == 407), start);

        if(CURLDIGEST_FINE != dig) {
          infof(data, "Authentication problem. Ignoring this.\n");
          data->state.authproblem = TRUE;
        }
      }
      else
#endif
      if(checkprefix("Basic", start)) {
        *availp |= CURLAUTH_BASIC;
        authp->avail |= CURLAUTH_BASIC;
        if(authp->picked == CURLAUTH_BASIC) {
          /* We asked for Basic authentication but got a 40X back
             anyway, which basicly means our name+password isn't
             valid. */
          authp->avail = CURLAUTH_NONE;
          infof(data, "Authentication problem. Ignoring this.\n");
          data->state.authproblem = TRUE;
        }
      }

  return CURLE_OK;
}