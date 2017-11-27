lt_user_data *
lt_dlloader_data (place)
     lt_dlloader *place;
{
  lt_user_data *data = 0;

  if (place)
    {
      LT_DLMUTEX_LOCK ();
      data = place ? &(place->dlloader_data) : 0;
      LT_DLMUTEX_UNLOCK ();
    }
  else
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_LOADER));
    }

  return data;
}