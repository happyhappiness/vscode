static void pop_clear_cache (POP_DATA *pop_data)
{
  int i;

  if (!pop_data->clear_cache)
    return;

  dprint (1, (debugfile, "pop_clear_cache: delete cached messages\n"));

  for (i = 0; i < POP_CACHE_LEN; i++)
  {
    if (pop_data->cache[i].path)
    {
      unlink (pop_data->cache[i].path);
      FREE (&pop_data->cache[i].path);
    }
  }
}