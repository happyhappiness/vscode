CURLSH *
curl_share_init(void)
{
  struct Curl_share *share =
    (struct Curl_share *)malloc(sizeof(struct Curl_share));
  if (share) {
    memset (share, 0, sizeof(struct Curl_share));
    share->specifier |= (1<<CURL_LOCK_DATA_SHARE);
  }

  return share;
}