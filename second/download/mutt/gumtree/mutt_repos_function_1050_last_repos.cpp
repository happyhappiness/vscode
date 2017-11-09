static int mdb_get_r_txn(header_cache_t *h)
{
  int rc;

  if (h->txn)
  {
    if (h->txn_mode == txn_read || h->txn_mode == txn_write)
      return MDB_SUCCESS;

    if ((rc = mdb_txn_renew (h->txn)) != MDB_SUCCESS)
    {
      h->txn = NULL;
      dprint (2, (debugfile, "mdb_get_r_txn: mdb_txn_renew: %s\n",
                  mdb_strerror (rc)));
      return rc;
    }
    h->txn_mode = txn_read;
    return rc;
  }

  if ((rc = mdb_txn_begin (h->env, NULL, MDB_RDONLY, &h->txn)) != MDB_SUCCESS)
  {
    h->txn = NULL;
    dprint (2, (debugfile, "mdb_get_r_txn: mdb_txn_begin: %s\n",
                mdb_strerror (rc)));
    return rc;
  }
  h->txn_mode = txn_read;
  return rc;
}