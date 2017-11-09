void mutt_hcache_free (void **data)
{
  if (!data || !*data)
    return;

#if HAVE_KC
  kcfree (*data);
  *data = NULL;
#elif HAVE_LMDB
  /* LMDB owns the data returned.  It should not be freed */
#else
  FREE (data);  /* __FREE_CHECKED__ */
#endif
}