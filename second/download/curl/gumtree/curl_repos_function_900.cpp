struct curl_fileinfo *Curl_fileinfo_alloc(void)
{
  struct curl_fileinfo *tmp = malloc(sizeof(struct curl_fileinfo));
  if(!tmp)
    return NULL;
  memset(tmp, 0, sizeof(struct curl_fileinfo));
  return tmp;
}