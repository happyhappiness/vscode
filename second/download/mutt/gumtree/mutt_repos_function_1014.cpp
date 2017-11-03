static void *
lazy_malloc(size_t siz)
{
  if (0 < siz && siz < 4096)
    siz = 4096;

  return safe_malloc(siz);
}