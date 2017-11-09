static void Curl_ossl_close_all(struct Curl_easy *data)
{
#ifdef HAVE_OPENSSL_ENGINE_H
  if(data->state.engine) {
    ENGINE_finish(data->state.engine);
    ENGINE_free(data->state.engine);
    data->state.engine = NULL;
  }
#else
  (void)data;
#endif
#if !defined(HAVE_ERR_REMOVE_THREAD_STATE_DEPRECATED) && \
  defined(HAVE_ERR_REMOVE_THREAD_STATE)
  /* OpenSSL 1.0.1 and 1.0.2 build an error queue that is stored per-thread
     so we need to clean it here in case the thread will be killed. All OpenSSL
     code should extract the error in association with the error so clearing
     this queue here should be harmless at worst. */
  ERR_remove_thread_state(NULL);
#endif
}