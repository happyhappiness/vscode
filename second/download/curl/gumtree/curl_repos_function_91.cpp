void static urlfree(struct UrlData *data, bool totally)
{
#ifdef USE_SSLEAY
  if (data->use_ssl) {
    if(data->ssl) {
      (void)SSL_shutdown(data->ssl);
      SSL_set_connect_state(data->ssl);

      SSL_free (data->ssl);
      data->ssl = NULL;
    }
    if(data->ctx) {
      SSL_CTX_free (data->ctx);
      data->ctx = NULL;
    }
    data->use_ssl = FALSE; /* get back to ordinary socket usage */
  }
#endif /* USE_SSLEAY */

  /* close possibly still open sockets */
  if(-1 != data->secondarysocket) {
    sclose(data->secondarysocket);
    data->secondarysocket = -1;	
  }
  if(-1 != data->firstsocket) {
    sclose(data->firstsocket);
    data->firstsocket=-1;
  }

  if(data->bits.proxystringalloc) {
    data->bits.proxystringalloc=FALSE;;
    free(data->proxy);
    data->proxy=NULL;

    /* Since we allocated the string the previous round, it means that we
       "discovered" the proxy in the environment variables and thus we must
       switch off that knowledge again... */
    data->bits.httpproxy=FALSE;
  }

  if(data->ptr_proxyuserpwd) {
    free(data->ptr_proxyuserpwd);
    data->ptr_proxyuserpwd=NULL;
  }
  if(data->ptr_uagent) {
    free(data->ptr_uagent);
    data->ptr_uagent=NULL;
  }
  if(data->ptr_userpwd) {
    free(data->ptr_userpwd);
    data->ptr_userpwd=NULL;
  }
  if(data->ptr_rangeline) {
    free(data->ptr_rangeline);
    data->ptr_rangeline=NULL;
  }
  if(data->ptr_ref) {
    free(data->ptr_ref);
    data->ptr_ref=NULL;
  }
  if(data->ptr_cookie) {
    free(data->ptr_cookie);
    data->ptr_cookie=NULL;
  }
  if(data->ptr_host) {
    free(data->ptr_host);
    data->ptr_host=NULL;
  }

  if(totally) {
    /* we let the switch decide whether we're doing a part or total
       cleanup */

    /* check for allocated [URL] memory to free: */
    if(data->freethis)
      free(data->freethis);

    if(data->headerbuff)
      free(data->headerbuff);

    if(data->free_referer)
      free(data->referer);

    cookie_cleanup(data->cookies);

    free(data);

    /* global cleanup */
    curl_free();
  }
}