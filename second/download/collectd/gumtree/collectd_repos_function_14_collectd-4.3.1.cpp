int
lt_dlmutex_register (lock, unlock, seterror, geterror)
     lt_dlmutex_lock *lock;
     lt_dlmutex_unlock *unlock;
     lt_dlmutex_seterror *seterror;
     lt_dlmutex_geterror *geterror;
{
  lt_dlmutex_unlock *old_unlock = lt_dlmutex_unlock_func;
  int		     errors	= 0;

  /* Lock using the old lock() callback, if any.  */
  LT_DLMUTEX_LOCK ();

  if ((lock && unlock && seterror && geterror)
      || !(lock || unlock || seterror || geterror))
    {
      lt_dlmutex_lock_func     = lock;
      lt_dlmutex_unlock_func   = unlock;
      lt_dlmutex_seterror_func = seterror;
      lt_dlmutex_geterror_func = geterror;
    }
  else
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_MUTEX_ARGS));
      ++errors;
    }

  /* Use the old unlock() callback we saved earlier, if any.  Otherwise
     record any errors using internal storage.  */
  if (old_unlock)
    (*old_unlock) ();

  /* Return the number of errors encountered during the execution of
     this function.  */
  return errors;
}