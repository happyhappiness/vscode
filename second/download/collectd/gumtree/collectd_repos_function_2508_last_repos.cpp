static int init_gcrypt() {
  /* http://lists.gnupg.org/pipermail/gcrypt-devel/2003-August/000458.html
   * Because you can't know in a library whether another library has
   * already initialized the library */
  if (gcry_control(GCRYCTL_ANY_INITIALIZATION_P))
    return (0);

/* http://www.gnupg.org/documentation/manuals/gcrypt/Multi_002dThreading.html
 * To ensure thread-safety, it's important to set GCRYCTL_SET_THREAD_CBS
 * *before* initalizing Libgcrypt with gcry_check_version(), which itself must
 * be called before any other gcry_* function. GCRYCTL_ANY_INITIALIZATION_P
 * above doesn't count, as it doesn't implicitly initalize Libgcrypt.
 *
 * tl;dr: keep all these gry_* statements in this exact order please. */
#if GCRYPT_VERSION_NUMBER < 0x010600
  if (gcry_control(GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread)) {
    return -1;
  }
#endif

  gcry_check_version(NULL);

  if (gcry_control(GCRYCTL_INIT_SECMEM, 32768)) {
    return -1;
  }

  gcry_control(GCRYCTL_INITIALIZATION_FINISHED);
  return 0;
}