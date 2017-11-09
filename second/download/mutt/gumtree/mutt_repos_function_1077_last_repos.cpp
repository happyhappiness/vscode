void *
mutt_hcache_fetch_raw (header_cache_t *h, const char *filename,
                       size_t(*keylen) (const char *fn))
{
#ifndef HAVE_DB4
  char path[_POSIX_PATH_MAX];
  int ksize;
#endif
#ifdef HAVE_QDBM
  char *data = NULL;
#elif HAVE_TC
  void *data;
  int sp;
#elif HAVE_KC
  void *data;
  size_t sp;
#elif HAVE_GDBM
  datum key;
  datum data;
#elif HAVE_DB4
  DBT key;
  DBT data;
#elif HAVE_LMDB
  MDB_val key;
  MDB_val data;
#endif

  if (!h)
    return NULL;

#ifdef HAVE_DB4
  if (filename[0] == '/')
    filename++;

  mutt_hcache_dbt_init(&key, (void *) filename, keylen(filename));
  mutt_hcache_dbt_empty_init(&data);
  data.flags = DB_DBT_MALLOC;

  h->db->get(h->db, NULL, &key, &data, 0);

  return data.data;
#else
  strncpy(path, h->folder, sizeof (path));
  safe_strcat(path, sizeof (path), filename);

  ksize = strlen (h->folder) + keylen (path + strlen (h->folder));  
#endif

#ifdef HAVE_QDBM
  data = vlget(h->db, path, ksize, NULL);

  return data;
#elif HAVE_TC
  data = tcbdbget(h->db, path, ksize, &sp);

  return data;
#elif HAVE_KC
  data = kcdbget(h->db, path, ksize, &sp);

  return data;
#elif HAVE_GDBM
  key.dptr = path;
  key.dsize = ksize;

  data = gdbm_fetch(h->db, key);

  return data.dptr;
#elif HAVE_LMDB
  key.mv_data = path;
  key.mv_size = ksize;
  if ((mdb_get_r_txn (h) != MDB_SUCCESS) ||
      (mdb_get (h->txn, h->db, &key, &data) != MDB_SUCCESS))
    return NULL;

  /* LMDB claims ownership of the returned data, so this will not be
   * freed in mutt_hcache_free(). */
  return data.mv_data;
#endif
}