size_t SyncTime_CURL_WriteOutput(void *ptr, size_t size, size_t nmemb,
                                 void *stream)
{
  fwrite(ptr, size, nmemb, stream);
  return (nmemb*size);
}