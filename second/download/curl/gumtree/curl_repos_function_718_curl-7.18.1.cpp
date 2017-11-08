static CURLcode parse_proxy_auth(struct SessionHandle *data,
                                 struct connectdata *conn)
{
  char proxyuser[MAX_CURL_USER_LENGTH]="";
  char proxypasswd[MAX_CURL_PASSWORD_LENGTH]="";

  sscanf(data->set.str[STRING_PROXYUSERPWD],
         "%" MAX_CURL_USER_LENGTH_TXT "[^:]:"
         "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^\n]",
         proxyuser, proxypasswd);

  conn->proxyuser = curl_easy_unescape(data, proxyuser, 0, NULL);
  if(!conn->proxyuser)
    return CURLE_OUT_OF_MEMORY;

  conn->proxypasswd = curl_easy_unescape(data, proxypasswd, 0, NULL);
  if(!conn->proxypasswd)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}