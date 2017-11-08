CURLcode Curl_output_digest(struct connectdata *conn,
                            bool proxy,
                            const unsigned char *request,
                            const unsigned char *uripath)
{
  CURLcode result;
  struct SessionHandle *data = conn->data;
  unsigned char *path;
  char *tmp;
  char *response;
  size_t len;
  bool have_chlg;

  /* Point to the address of the pointer that holds the string to send to the
     server, which is for a plain host or for a HTTP proxy */
  char **allocuserpwd;

  /* Point to the name and password for this */
  const char *userp;
  const char *passwdp;

  /* Point to the correct struct with this */
  struct digestdata *digest;
  struct auth *authp;

  if(proxy) {
    digest = &data->state.proxydigest;
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->proxyuser;
    passwdp = conn->proxypasswd;
    authp = &data->state.authproxy;
  }
  else {
    digest = &data->state.digest;
    allocuserpwd = &conn->allocptr.userpwd;
    userp = conn->user;
    passwdp = conn->passwd;
    authp = &data->state.authhost;
  }

  Curl_safefree(*allocuserpwd);

  /* not set means empty */
  if(!userp)
    userp = "";

  if(!passwdp)
    passwdp = "";

#if defined(USE_WINDOWS_SSPI)
  have_chlg = digest->input_token ? TRUE : FALSE;
#else
  have_chlg = digest->nonce ? TRUE : FALSE;
#endif

  if(!have_chlg) {
    authp->done = FALSE;
    return CURLE_OK;
  }

  /* So IE browsers < v7 cut off the URI part at the query part when they
     evaluate the MD5 and some (IIS?) servers work with them so we may need to
     do the Digest IE-style. Note that the different ways cause different MD5
     sums to get sent.

     Apache servers can be set to do the Digest IE-style automatically using
     the BrowserMatch feature:
     http://httpd.apache.org/docs/2.2/mod/mod_auth_digest.html#msie

     Further details on Digest implementation differences:
     http://www.fngtps.com/2006/09/http-authentication
  */

  if(authp->iestyle && ((tmp = strchr((char *)uripath, '?')) != NULL)) {
    size_t urilen = tmp - (char *)uripath;

    path = (unsigned char *) aprintf("%.*s", urilen, uripath);
  }
  else
    path = (unsigned char *) strdup((char *) uripath);

  if(!path)
    return CURLE_OUT_OF_MEMORY;

  result = Curl_sasl_create_digest_http_message(data, userp, passwdp, request,
                                                path, digest, &response, &len);
  free(path);
  if(result)
    return result;

  *allocuserpwd = aprintf("%sAuthorization: Digest %s\r\n",
                          proxy ? "Proxy-" : "",
                          response);
  free(response);
  if(!*allocuserpwd)
    return CURLE_OUT_OF_MEMORY;

  authp->done = TRUE;

  return CURLE_OK;
}