void *
lt__malloc (size_t n)
{
  void *mem;

  if (! (mem = malloc (n)))
    (*lt__alloc_die) ();

  return mem;
}