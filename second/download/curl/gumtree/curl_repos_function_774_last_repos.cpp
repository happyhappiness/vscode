void fuzz_free(void **ptr)
{
  if(*ptr != NULL) {
    free(*ptr);
    *ptr = NULL;
  }
}