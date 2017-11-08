bool
Curl_ssl_config_matches(struct ssl_primary_config* data,
                        struct ssl_primary_config* needle)
{
  if((data->version == needle->version) &&
     (data->version_max == needle->version_max) &&
     (data->verifypeer == needle->verifypeer) &&
     (data->verifyhost == needle->verifyhost) &&
     Curl_safe_strcasecompare(data->CApath, needle->CApath) &&
     Curl_safe_strcasecompare(data->CAfile, needle->CAfile) &&
     Curl_safe_strcasecompare(data->clientcert, needle->clientcert) &&
     Curl_safe_strcasecompare(data->cipher_list, needle->cipher_list))
    return TRUE;

  return FALSE;
}