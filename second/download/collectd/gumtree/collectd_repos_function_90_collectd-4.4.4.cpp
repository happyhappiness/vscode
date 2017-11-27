lt_dlcaller_id
lt_dlcaller_register ()
{
  static lt_dlcaller_id last_caller_id = 0;
  int result;

  LT_DLMUTEX_LOCK ();
  result = ++last_caller_id;
  LT_DLMUTEX_UNLOCK ();

  return result;
}