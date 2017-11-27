const char *
lt_dlloader_name (place)
     lt_dlloader *place;
{
  const char *name = 0;

  if (place)
    {
      LT_DLMUTEX_LOCK ();
      name = place ? place->loader_name : 0;
      LT_DLMUTEX_UNLOCK ();
    }
  else
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_LOADER));
    }

  return name;
}