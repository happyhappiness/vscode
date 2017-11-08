struct Curl_share *
curl_share_init(void)
{
  struct Curl_share *share = calloc(1, sizeof(struct Curl_share));
  if(share) {
    share->specifier |= (1<<CURL_LOCK_DATA_SHARE);

    if(Curl_mk_dnscache(&share->hostcache)) {
      free(share);
      return NULL;
    }
  }

  return share;
}