void imap_expunge_mailbox (IMAP_DATA* idata)
{
  HEADER* h;
  int i, cacheno;

#ifdef USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);
#endif

  for (i = 0; i < idata->ctx->msgcount; i++)
  {
    h = idata->ctx->hdrs[i];

    if (h->index == -1)
    {
      dprint (2, (debugfile, "Expunging message UID %d.\n", HEADER_DATA (h)->uid));

      h->active = 0;
      idata->ctx->size -= h->content->length;

      imap_cache_del (idata, h);
#if USE_HCACHE
      imap_hcache_del (idata, HEADER_DATA(h)->uid);
#endif

      /* free cached body from disk, if necessary */
      cacheno = HEADER_DATA(h)->uid % IMAP_CACHE_LEN;
      if (idata->cache[cacheno].uid == HEADER_DATA(h)->uid &&
	  idata->cache[cacheno].path)
      {
	unlink (idata->cache[cacheno].path);
	FREE (&idata->cache[cacheno].path);
      }

      imap_free_header_data ((IMAP_HEADER_DATA**)&h->data);
    }
  }

#if USE_HCACHE
  imap_hcache_close (idata);
#endif

  /* We may be called on to expunge at any time. We can't rely on the caller
   * to always know to rethread */
  mx_update_tables (idata->ctx, 0);
  mutt_sort_headers (idata->ctx, 1);
}