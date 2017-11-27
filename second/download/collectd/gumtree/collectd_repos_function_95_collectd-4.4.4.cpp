lt_dlloader *
lt_dlloader_next (place)
     lt_dlloader *place;
{
  lt_dlloader *next;

  LT_DLMUTEX_LOCK ();
  next = place ? place->next : loaders;
  LT_DLMUTEX_UNLOCK ();

  return next;
}