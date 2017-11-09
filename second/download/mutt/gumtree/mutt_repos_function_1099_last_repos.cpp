void
mutt_hcache_close(header_cache_t *h)
{
  int rc;

  if (!h)
    return;

  if (h->txn)
  {
    if (h->txn_mode == txn_write)
    {
      if ((rc = mdb_txn_commit (h->txn)) != MDB_SUCCESS)
      {
        dprint (2, (debugfile, "mutt_hcache_close: mdb_txn_commit: %s\n",
                    mdb_strerror (rc)));
      }
    }
    else
      mdb_txn_abort (h->txn);
    h->txn_mode = txn_uninitialized;
    h->txn = NULL;
  }

  mdb_env_close(h->env);
  FREE (&h->folder);
  FREE (&h);
}