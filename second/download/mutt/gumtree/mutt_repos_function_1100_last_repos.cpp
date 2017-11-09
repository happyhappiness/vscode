int
mutt_hcache_delete(header_cache_t *h, const char *filename,
		   size_t(*keylen) (const char *fn))
{
  char path[_POSIX_PATH_MAX];
  int ksize;
  MDB_val key;
  int rc;

  if (!h)
    return -1;

  strncpy(path, h->folder, sizeof (path));
  safe_strcat(path, sizeof (path), filename);
  ksize = strlen (h->folder) + keylen (path + strlen (h->folder));

  key.mv_data = path;
  key.mv_size = ksize;
  if (mdb_get_w_txn(h) != MDB_SUCCESS)
    return -1;
  rc = mdb_del(h->txn, h->db, &key, NULL);
  if (rc != MDB_SUCCESS && rc != MDB_NOTFOUND)
  {
    dprint (2, (debugfile, "mutt_hcache_delete: mdb_del: %s\n",
                mdb_strerror (rc)));
    mdb_txn_abort(h->txn);
    h->txn_mode = txn_uninitialized;
    h->txn = NULL;
    return -1;
  }

  return 0;
}