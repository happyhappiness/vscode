void *custom_realloc(void *ptr, size_t size)
{
  if(!seen_realloc && seen_malloc) {
    printf("seen custom_realloc()\n");
    seen_realloc = 1;
  }
  return (realloc)(ptr, size);
}