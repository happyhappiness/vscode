const char *mutt_hcache_backend (void)
{
  return "lmdb " MDB_VERSION_STRING;
}