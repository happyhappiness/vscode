CURLSHcode
Curl_share_lock(struct SessionHandle *data, curl_lock_data type, curl_lock_access access)
{
  struct Curl_share *share = data->share;

  if (share == NULL)
    return CURLSHE_INVALID;

  if(share->specifier & (1<<type)) {
    share->lockfunc (data, type, access, share->clientdata);
  }
  /* else if we don't share this, pretend successful lock */

  return CURLSHE_OK;
}