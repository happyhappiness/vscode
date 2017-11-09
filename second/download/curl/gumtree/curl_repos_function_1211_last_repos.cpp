static int sshkeycallback(struct Curl_easy *easy,
                          const struct curl_khkey *knownkey, /* known */
                          const struct curl_khkey *foundkey, /* found */
                          enum curl_khmatch match,
                          void *clientp)
{
  (void)easy;
  (void)knownkey;
  (void)foundkey;
  (void)clientp;

  /* we only allow perfect matches, and we reject everything else */
  return (match != CURLKHMATCH_OK)?CURLKHSTAT_REJECT:CURLKHSTAT_FINE;
}