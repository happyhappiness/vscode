static CURLcode
darwinssl_connect_step3(struct connectdata *conn,
                        int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  /* There is no step 3!
   * Well, okay, if verbose mode is on, let's print the details of the
   * server certificates. */
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  if(data->set.verbose)
    show_verbose_server_cert(conn, sockindex);
#endif

  connssl->connecting_state = ssl_connect_done;
  return CURLE_OK;
}