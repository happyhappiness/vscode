static size_t write_cb(void *ptr, size_t size, size_t nmemb, void *data)
{

  size_t written = size * nmemb;
  char* pBuffer = (char *) malloc(written + 1);

  strncpy(pBuffer, (const char *)ptr, written);
  pBuffer[written] = '\0';

  fprintf(MSG_OUT, "%s", pBuffer);

  free(pBuffer);

  return written;
}