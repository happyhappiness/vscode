int Curl_ossl_close_all(struct SessionHandle *data)
{
  /*
    ERR_remove_state() frees the error queue associated with
    thread pid.  If pid == 0, the current thread will have its
    error queue removed.

    Since error queue data structures are allocated
    automatically for new threads, they must be freed when
    threads are terminated in oder to avoid memory leaks.
  */
  ERR_remove_state(0);

#ifdef HAVE_OPENSSL_ENGINE_H
  if(data->state.engine) {
    ENGINE_finish(data->state.engine);
    ENGINE_free(data->state.engine);
    data->state.engine = NULL;
  }
#else
  (void)data;
#endif
  return 0;
}