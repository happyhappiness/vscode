const char *mutt_hcache_backend (void)
{
  static char backend[SHORT_STRING];
  snprintf(backend, sizeof(backend), "kyotocabinet %s", KCVERSION);
  return backend;
}