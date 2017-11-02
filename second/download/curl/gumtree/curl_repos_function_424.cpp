void *custom_calloc(size_t nmemb, size_t size)
{
  if(!seen_calloc) {
    printf("seen custom_calloc()\n");
    seen_calloc = 1;
  }
  return (calloc)(nmemb, size);
}