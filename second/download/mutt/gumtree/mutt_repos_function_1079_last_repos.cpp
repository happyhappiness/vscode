int
mutt_hcache_store_raw (header_cache_t* h, const char* filename, void* data,
                       size_t dlen, size_t(*keylen) (const char* fn))
{
#ifndef HAVE_DB4
  char path[_POSIX_PATH_MAX];
  int ksize;
#endif
#if HAVE_GDBM
  datum key;
  datum databuf;
#elif HAVE_DB4
  DBT key;
  DBT databuf;
#elif HAVE_LMDB
  MDB_val key;
  MDB_val databuf;
  int rc;
#endif

  if (!h)
    return -1;

#if HAVE_DB4
  if (filename[0] == '/')
    filename++;

  mutt_hcache_dbt_init(&key, (void *) filename, keylen(filename));

  mutt_hcache_dbt_empty_init(&databuf);
  databuf.flags = DB_DBT_USERMEM;
  databuf.data = data;
  databuf.size = dlen;
  databuf.ulen = dlen;

  return h->db->put(h->db, NULL, &key, &databuf, 0);
#else
  strncpy(path, h->folder, sizeof (path));
  safe_strcat(path, sizeof (path), filename);

  ksize = strlen(h->folder) + keylen(path + strlen(h->folder));
#endif

#if HAVE_QDBM
  return vlput(h->db, path, ksize, data, dlen, VL_DOVER);
#elif HAVE_TC
  return tcbdbput(h->db, path, ksize, data, dlen);
#elif HAVE_KC
  return kcdbset(h->db, path, ksize, data, dlen);
#elif HAVE_GDBM
  key.dptr = path;
  key.dsize = ksize;

  databuf.dsize = dlen;
  databuf.dptr = data;

  return gdbm_store(h->db, key, databuf, GDBM_REPLACE);
#elif HAVE_LMDB
  key.mv_data = path;
  key.mv_size = ksize;
  databuf.mv_data = data;
  databuf.mv_size = dlen;
  if ((rc = mdb_get_w_txn (h)) != MDB_SUCCESS)
    return rc;

  if ((rc = mdb_put (h->txn, h->db, &key, &databuf, 0)) != MDB_SUCCESS)
  {
    dprint (2, (debugfile, "mutt_hcache_store_raw: mdb_put: %s\n",
                mdb_strerror(rc)));
    mdb_txn_abort (h->txn);
    h->txn_mode = txn_uninitialized;
    h->txn = NULL;
  }
  return rc;
#endif
}