void *custom_malloc(size_t size)
{
  if(!seen_malloc && seen_calloc) {
    printf("seen custom_malloc()\n");
    seen_malloc = 1;
  }
  return (malloc)(size);
}