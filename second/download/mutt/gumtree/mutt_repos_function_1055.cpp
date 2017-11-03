void
mutt_hcache_close(header_cache_t *h)
{
  if (!h)
    return;

  h->db->close (h->db, 0);
  h->env->close (h->env, 0);
  mx_unlock_file (h->lockfile, h->fd, 0);
  close (h->fd);
  unlink (h->lockfile);
  FREE (&h->folder);
  FREE (&h);
}