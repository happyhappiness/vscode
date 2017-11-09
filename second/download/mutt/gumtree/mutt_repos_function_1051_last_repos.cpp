static int mdb_get_w_txn(header_cache_t *h)
{
  int rc;

  if (h->txn)
  {
    if (h->txn_mode == txn_write)
      return MDB_SUCCESS;

    /* Free up the memory for readonly or reset transactions */
    mdb_txn_abort (h->txn);
  }

  if ((rc = mdb_txn_begin (h->env, NULL, 0, &h->txn)) != MDB_SUCCESS)
  {
    h->txn = NULL;
    dprint (2, (debugfile, "mdb_get_w_txn: mdb_txn_begin %s\n",
                mdb_strerror (rc)));
    return rc;
  }

  h->txn_mode = txn_write;
  return rc;
}