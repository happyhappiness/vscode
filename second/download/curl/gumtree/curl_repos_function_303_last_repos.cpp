static char *
buffer_undef(localkey_t key, long size)

{
  /* Define the buffer system, get the buffer for the given local key in
     the current thread, and make sure it is at least `size'-byte long.
     Set `size' to < 0 to get its address only. */

  pthread_mutex_lock(&mutex);

  /* Determine if we can use pthread-specific data. */

  if(Curl_thread_buffer == buffer_undef) {      /* If unchanged during lock. */
    if(!pthread_key_create(&thdkey, thdbufdestroy))
      Curl_thread_buffer = buffer_threaded;
    else if(!(locbufs = calloc((size_t) LK_LAST, sizeof *locbufs))) {
      pthread_mutex_unlock(&mutex);
      return (char *) NULL;
      }
    else
        Curl_thread_buffer = buffer_unthreaded;

    atexit(terminate);
    }

  pthread_mutex_unlock(&mutex);
  return Curl_thread_buffer(key, size);
}