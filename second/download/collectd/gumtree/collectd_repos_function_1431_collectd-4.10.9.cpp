static void network_init_gcrypt (void) /* {{{ */
{
  /* http://lists.gnupg.org/pipermail/gcrypt-devel/2003-August/000458.html
   * Because you can't know in a library whether another library has
   * already initialized the library */
  if (gcry_control (GCRYCTL_ANY_INITIALIZATION_P))
    return;

  gcry_check_version (NULL); /* before calling any other functions */
  gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
  gcry_control (GCRYCTL_INIT_SECMEM, 32768);
  gcry_control (GCRYCTL_INITIALIZATION_FINISHED);
}