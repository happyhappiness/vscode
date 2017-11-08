static CURLcode
Curl_http_output_auth(struct connectdata *conn,
                      char *request,
                      char *path,
                      bool proxytunnel) /* TRUE if this is the request setting
                                           up the proxy tunnel */
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *auth=NULL;
  struct auth *authhost;
  struct auth *authproxy;

  curlassert(data);

  authhost = &data->state.authhost;
  authproxy = &data->state.authproxy;

  if((conn->bits.httpproxy && conn->bits.proxy_user_passwd) ||
     conn->bits.user_passwd)
    /* continue please */ ;
  else {
    authhost->done = TRUE;
    authproxy->done = TRUE;
    return CURLE_OK; /* no authentication with no user or password */
  }

  if(authhost->want && !authhost->picked)
    /* The app has selected one or more methods, but none has been picked
       so far by a server round-trip. Then we set the picked one to the
       want one, and if this is one single bit it'll be used instantly. */
    authhost->picked = authhost->want;

  if(authproxy->want && !authproxy->picked)
    /* The app has selected one or more methods, but none has been picked so
       far by a proxy round-trip. Then we set the picked one to the want one,
       and if this is one single bit it'll be used instantly. */
    authproxy->picked = authproxy->want;

  /* Send proxy authentication header if needed */
  if (conn->bits.httpproxy &&
      (conn->bits.tunnel_proxy == proxytunnel)) {
#ifdef USE_NTLM
    if(authproxy->picked == CURLAUTH_NTLM) {
      auth=(char *)"NTLM";
      result = Curl_output_ntlm(conn, TRUE);
      if(result)
        return result;
    }
    else
#endif
      if(authproxy->picked == CURLAUTH_BASIC) {
        /* Basic */
        if(conn->bits.proxy_user_passwd &&
           !checkheaders(data, "Proxy-authorization:")) {
          auth=(char *)"Basic";
          result = Curl_output_basic(conn, TRUE);
          if(result)
            return result;
        }
        /* NOTE: Curl_output_basic() should set 'done' TRUE, as the other auth
           functions work that way */
        authproxy->done = TRUE;
      }
#ifndef CURL_DISABLE_CRYPTO_AUTH
      else if(authproxy->picked == CURLAUTH_DIGEST) {
        auth=(char *)"Digest";
        result = Curl_output_digest(conn,
                                    TRUE, /* proxy */
                                    (unsigned char *)request,
                                    (unsigned char *)path);
        if(result)
          return result;
      }
#endif
      if(auth) {
        infof(data, "Proxy auth using %s with user '%s'\n",
              auth, conn->proxyuser?conn->proxyuser:"");
        authproxy->multi = !authproxy->done;
      }
      else
        authproxy->multi = FALSE;
    }
  else
    /* we have no proxy so let's pretend we're done authenticating
       with it */
    authproxy->done = TRUE;

  /* To prevent the user+password to get sent to other than the original
     host due to a location-follow, we do some weirdo checks here */
  if(!data->state.this_is_a_follow ||
     conn->bits.netrc ||
     !data->state.first_host ||
     curl_strequal(data->state.first_host, conn->host.name) ||
     data->set.http_disable_hostname_check_before_authentication) {

    /* Send web authentication header if needed */
    {
      auth = NULL;
#ifdef HAVE_GSSAPI
      if((authhost->picked == CURLAUTH_GSSNEGOTIATE) &&
         data->state.negotiate.context &&
         !GSS_ERROR(data->state.negotiate.status)) {
        auth=(char *)"GSS-Negotiate";
        result = Curl_output_negotiate(conn);
        if (result)
          return result;
        authhost->done = TRUE;
      }
      else
#endif
#ifdef USE_NTLM
      if(authhost->picked == CURLAUTH_NTLM) {
        auth=(char *)"NTLM";
        result = Curl_output_ntlm(conn, FALSE);
        if(result)
          return result;
      }
      else
#endif
      {
#ifndef CURL_DISABLE_CRYPTO_AUTH
        if(authhost->picked == CURLAUTH_DIGEST) {
          auth=(char *)"Digest";
          result = Curl_output_digest(conn,
                                      FALSE, /* not a proxy */
                                      (unsigned char *)request,
                                      (unsigned char *)path);
          if(result)
            return result;
        } else
#endif
        if(authhost->picked == CURLAUTH_BASIC) {
          if(conn->bits.user_passwd &&
             !checkheaders(data, "Authorization:")) {
            auth=(char *)"Basic";
            result = Curl_output_basic(conn, FALSE);
            if(result)
              return result;
          }
          /* basic is always ready */
          authhost->done = TRUE;
        }
      }
      if(auth) {
        infof(data, "Server auth using %s with user '%s'\n",
              auth, conn->user);

        authhost->multi = !authhost->done;
      }
      else
        authhost->multi = FALSE;
    }
  }
  else
    authhost->done = TRUE;

  return result;
}