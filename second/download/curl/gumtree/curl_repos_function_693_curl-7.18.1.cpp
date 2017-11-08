bool Curl_isPipeliningEnabled(const struct SessionHandle *handle)
{
  if(handle->multi && Curl_multi_canPipeline(handle->multi))
    return TRUE;

  return FALSE;
}