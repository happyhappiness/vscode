static int
hcache_open_db4 (struct header_cache* h, const char* path)
{
  struct stat sb;
  int ret;
  u_int32_t createflags = DB_CREATE;
  int pagesize;

  if (mutt_atoi (HeaderCachePageSize, &pagesize) < 0 || pagesize <= 0)
    pagesize = 16384;

  snprintf (h->lockfile, _POSIX_PATH_MAX, "%s-lock-hack", path);

  h->fd = open (h->lockfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (h->fd < 0)
    return -1;

  if (mx_lock_file (h->lockfile, h->fd, 1, 0, 5))
    goto fail_close;

  ret = db_env_create (&h->env, 0);
  if (ret)
    goto fail_unlock;

  ret = (*h->env->open)(h->env, NULL, DB_INIT_MPOOL | DB_CREATE | DB_PRIVATE,
	0600);
  if (ret)
    goto fail_env;

  ret = db_create (&h->db, h->env, 0);
  if (ret)
    goto fail_env;

  if (stat(path, &sb) != 0 && errno == ENOENT)
  {
    createflags |= DB_EXCL;
    h->db->set_pagesize(h->db, pagesize);
  }

  ret = (*h->db->open)(h->db, NULL, path, h->folder, DB_BTREE, createflags,
                       0600);
  if (ret)
    goto fail_db;

  return 0;

  fail_db:
  h->db->close (h->db, 0);
  fail_env:
  h->env->close (h->env, 0);
  fail_unlock:
  mx_unlock_file (h->lockfile, h->fd, 0);
  fail_close:
  close (h->fd);
  unlink (h->lockfile);

  return -1;
}