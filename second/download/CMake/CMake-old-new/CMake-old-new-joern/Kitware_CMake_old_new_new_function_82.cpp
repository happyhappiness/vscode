static CURLcode http_output_basic(struct connectdata *conn, bool proxy)
{
  size_t size = 0;
  char *authorization = NULL;
  struct Curl_easy *data = conn->data;
  char **userp;
  const char *user;
  const char *pwd;
  CURLcode result;
  char *out;

  if(proxy) {
    userp = &conn->allocptr.proxyuserpwd;
    user = conn->http_proxy.user;
    pwd = conn->http_proxy.passwd;
  }
  else {
    userp = &conn->allocptr.userpwd;
    user = conn->user;
    pwd = conn->passwd;
  }

  out = aprintf("%s:%s", user, pwd);
  if(!out)
    return CURLE_OUT_OF_MEMORY;

  result = Curl_base64_encode(data, out, strlen(out), &authorization, &size);
  if(result)
    goto fail;

  if(!authorization) {
    result = CURLE_REMOTE_ACCESS_DENIED;
    goto fail;
  }

  free(*userp);
  *userp = aprintf("%sAuthorization: Basic %s\r\n",
                   proxy ? "Proxy-" : "",
                   authorization);
  free(authorization);
  if(!*userp) {
    result = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  fail:
  free(out);
  return result;
}