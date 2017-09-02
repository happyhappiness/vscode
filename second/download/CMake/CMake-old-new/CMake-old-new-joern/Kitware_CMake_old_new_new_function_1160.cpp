static CURLcode Curl_output_basic(struct connectdata *conn, bool proxy)
{
  char *authorization;
  struct SessionHandle *data=conn->data;
  char **userp;
  char *user;
  char *pwd;

  if(proxy) {
    userp = &conn->allocptr.proxyuserpwd;
    user = conn->proxyuser;
    pwd = conn->proxypasswd;
  }
  else {
    userp = &conn->allocptr.userpwd;
    user = conn->user;
    pwd = conn->passwd;
  }

  snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);
  if(Curl_base64_encode(data, data->state.buffer,
                        strlen(data->state.buffer),
                        &authorization) > 0) {
    if(*userp)
      free(*userp);
    *userp = aprintf( "%sAuthorization: Basic %s\r\n",
                      proxy?"Proxy-":"",
                      authorization);
    free(authorization);
  }
  else
    return CURLE_OUT_OF_MEMORY;
  return CURLE_OK;
}