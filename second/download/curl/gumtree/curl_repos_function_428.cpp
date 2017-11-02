void custom_free(void *ptr)
{
  if(!seen_free && seen_realloc) {
    printf("seen custom_free()\n");
    seen_free = 1;
  }
  (free)(ptr);
}