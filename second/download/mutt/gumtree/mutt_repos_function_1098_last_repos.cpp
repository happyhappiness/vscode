static int
hcache_open_lmdb (struct header_cache* h, const char* path)
{
  int rc;

  h->txn = NULL;

  if ((rc = mdb_env_create(&h->env)) != MDB_SUCCESS)
  {
    dprint (2, (debugfile, "hcache_open_lmdb: mdb_env_create: %s\n",
                mdb_strerror(rc)));
    return -1;
  }

  mdb_env_set_mapsize(h->env, LMDB_DB_SIZE);

  if ((rc = mdb_env_open(h->env, path, MDB_NOSUBDIR, 0644)) != MDB_SUCCESS)
  {
    dprint (2, (debugfile, "hcache_open_lmdb: mdb_env_open: %s\n",
                mdb_strerror(rc)));
    goto fail_env;
  }

  if ((rc = mdb_get_r_txn(h)) != MDB_SUCCESS)
    goto fail_env;

  if ((rc = mdb_dbi_open(h->txn, NULL, MDB_CREATE, &h->db)) != MDB_SUCCESS)
  {
    dprint (2, (debugfile, "hcache_open_lmdb: mdb_dbi_open: %s\n",
                mdb_strerror(rc)));
    goto fail_dbi;
  }

  mdb_txn_reset(h->txn);
  h->txn_mode = txn_uninitialized;
  return 0;

fail_dbi:
  mdb_txn_abort(h->txn);
  h->txn_mode = txn_uninitialized;
  h->txn = NULL;

fail_env:
  mdb_env_close(h->env);
  return -1;
}