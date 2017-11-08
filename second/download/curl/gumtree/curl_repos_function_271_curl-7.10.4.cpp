CURLSHcode curl_share_cleanup(CURLSH *sh)
{
  struct Curl_share *share = (struct Curl_share *)sh;
  if (share->dirty)
    return CURLSHE_IN_USE;

  free (share);
  
  return CURLSHE_OK;
}