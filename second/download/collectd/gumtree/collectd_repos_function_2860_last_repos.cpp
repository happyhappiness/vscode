static void set_thread_name(pthread_t tid, char const *name) {
#if defined(HAVE_PTHREAD_SETNAME_NP) || defined(HAVE_PTHREAD_SET_NAME_NP)

  /* glibc limits the length of the name and fails if the passed string
   * is too long, so we truncate it here. */
  char n[THREAD_NAME_MAX];
  if (strlen(name) >= THREAD_NAME_MAX)
    WARNING("set_thread_name(\"%s\"): name too long", name);
  sstrncpy(n, name, sizeof(n));

#if defined(HAVE_PTHREAD_SETNAME_NP)
  int status = pthread_setname_np(tid, n);
  if (status != 0) {
    char errbuf[1024];
    ERROR("set_thread_name(\"%s\"): %s", n,
          sstrerror(status, errbuf, sizeof(errbuf)));
  }
#else /* if defined(HAVE_PTHREAD_SET_NAME_NP) */
  pthread_set_name_np(tid, n);
#endif

#endif
}