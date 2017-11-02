static void
terminate(void)

{
  if(Curl_thread_buffer == buffer_threaded) {
    locbufs = pthread_getspecific(thdkey);
    pthread_setspecific(thdkey, (void *) NULL);
    pthread_key_delete(thdkey);
    }

  if(Curl_thread_buffer != buffer_undef) {
    thdbufdestroy((void *) locbufs);
    locbufs = (buffer_t *) NULL;
    }

  Curl_thread_buffer = buffer_undef;
}