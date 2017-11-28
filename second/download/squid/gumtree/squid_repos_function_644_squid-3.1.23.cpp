void *
lt__realloc (void *mem, size_t n)
{
  if (! (mem = realloc (mem, n)))
    (*lt__alloc_die) ();

  return mem;
}