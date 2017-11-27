static int cj_init (void) /* {{{ */
{
  /* Call this while collectd is still single-threaded to avoid
   * initialization issues in libgcrypt. */
  curl_global_init (CURL_GLOBAL_SSL);
  return (0);
}