static void
lazy_realloc(void *ptr, size_t siz)
{
  void **p = (void **) ptr;

  if (p != NULL && 0 < siz && siz < 4096)
    return;

  safe_realloc(ptr, siz);
}