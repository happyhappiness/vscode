{
  if((data->proxytype == needle->proxytype) &&
     (data->port == needle->port) &&
     Curl_safe_strcasecompare(data->host.name, needle->host.name))
    return TRUE;

  return FALSE;
}