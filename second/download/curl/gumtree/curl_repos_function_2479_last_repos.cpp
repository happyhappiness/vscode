static void *Curl_schannel_get_internals(struct ssl_connect_data *connssl,
                                         CURLINFO info UNUSED_PARAM)
{
  (void)info;
  return &BACKEND->ctxt->ctxt_handle;
}