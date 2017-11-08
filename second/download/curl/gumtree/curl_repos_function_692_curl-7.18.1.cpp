static bool IsPipeliningPossible(const struct SessionHandle *handle)
{
  if(handle->multi && Curl_multi_canPipeline(handle->multi) &&
      (handle->set.httpreq == HTTPREQ_GET ||
       handle->set.httpreq == HTTPREQ_HEAD) &&
      handle->set.httpversion != CURL_HTTP_VERSION_1_0)
    return TRUE;

  return FALSE;
}