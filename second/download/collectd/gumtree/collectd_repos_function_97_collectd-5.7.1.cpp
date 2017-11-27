const lt_dlvtable *
lt_dlloader_find (const char *name)
{
  return lt_dlloader_get (slist_find (loaders, loader_callback, (void *) name));
}