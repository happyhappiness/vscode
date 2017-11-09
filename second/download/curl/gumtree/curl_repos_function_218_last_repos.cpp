size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  /* printf("write_file\n"); */
  return fwrite(ptr, size, nmemb, stream);
}