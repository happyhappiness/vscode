lt_dlloader *
lt_dlloader_find (loader_name)
     const char *loader_name;
{
  lt_dlloader *place = 0;

  LT_DLMUTEX_LOCK ();
  for (place = loaders; place; place = place->next)
    {
      if (strcmp (place->loader_name, loader_name) == 0)
	{
	  break;
	}
    }
  LT_DLMUTEX_UNLOCK ();

  return place;
}