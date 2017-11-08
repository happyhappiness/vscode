CURLSHcode
Curl_share_unlock(struct Curl_easy *data, curl_lock_data type)
{
  struct Curl_share *share = data->share;

  if(share == NULL)
    return CURLSHE_INVALID;

  if(share->specifier & (1<<type)) {
    if(share->unlockfunc) /* only call this if set! */
      share->unlockfunc (data, type, share->clientdata);
  }

  return CURLSHE_OK;
}