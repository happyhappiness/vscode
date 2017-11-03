int mutt_bcache_commit(body_cache_t* bcache, const char* id)
{
  char tmpid[_POSIX_PATH_MAX];

  snprintf (tmpid, sizeof (tmpid), "%s.tmp", id);

  return mutt_bcache_move (bcache, tmpid, id);
}