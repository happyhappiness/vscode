void Curl_safefree(void *ptr)
{
  if(ptr)
    free(ptr);
}