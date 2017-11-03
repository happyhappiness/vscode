IMAP_STATUS* imap_mboxcache_get (IMAP_DATA* idata, const char* mbox, int create)
{
  LIST* cur;
  IMAP_STATUS* status;
  IMAP_STATUS scache;
#ifdef USE_HCACHE
  header_cache_t *hc = NULL;
  unsigned int *uidvalidity = NULL;
  unsigned int *uidnext = NULL;
#endif

  for (cur = idata->mboxcache; cur; cur = cur->next)
  {
    status = (IMAP_STATUS*)cur->data;

    if (!imap_mxcmp (mbox, status->name))
      return status;
  }
  status = NULL;

  /* lame */
  if (create)
  {
    memset (&scache, 0, sizeof (scache));
    scache.name = (char*)mbox;
    idata->mboxcache = mutt_add_list_n (idata->mboxcache, &scache,
                                        sizeof (scache));
    status = imap_mboxcache_get (idata, mbox, 0);
    status->name = safe_strdup (mbox);
  }

#ifdef USE_HCACHE
  hc = imap_hcache_open (idata, mbox);
  if (hc)
  {
    uidvalidity = mutt_hcache_fetch_raw (hc, "/UIDVALIDITY", imap_hcache_keylen);
    uidnext = mutt_hcache_fetch_raw (hc, "/UIDNEXT", imap_hcache_keylen);
    mutt_hcache_close (hc);
    if (uidvalidity)
    {
      if (!status)
      {
        FREE (&uidvalidity);
        FREE (&uidnext);
        return imap_mboxcache_get (idata, mbox, 1);
      }
      status->uidvalidity = *uidvalidity;
      status->uidnext = uidnext ? *uidnext: 0;
      dprint (3, (debugfile, "mboxcache: hcache uidvalidity %d, uidnext %d\n",
                  status->uidvalidity, status->uidnext));
    }
    FREE (&uidvalidity);
    FREE (&uidnext);
  }
#endif

  return status;
}