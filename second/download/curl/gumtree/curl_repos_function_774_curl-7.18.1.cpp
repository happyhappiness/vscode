CURLMcode curl_multi_cleanup(CURLM *multi_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  struct Curl_one_easy *nexteasy;
  int i;
  struct closure *cl;
  struct closure *n;

  if(GOOD_MULTI_HANDLE(multi)) {
    multi->type = 0; /* not good anymore */
    Curl_hash_destroy(multi->hostcache);
    Curl_hash_destroy(multi->sockhash);

    /* go over all connections that have close actions */
    for(i=0; i< multi->connc->num; i++) {
      if(multi->connc->connects[i] &&
         multi->connc->connects[i]->protocol & PROT_CLOSEACTION) {
        Curl_disconnect(multi->connc->connects[i]);
        multi->connc->connects[i] = NULL;
      }
    }
    /* now walk through the list of handles we kept around only to be
       able to close connections "properly" */
    cl = multi->closure;
    while(cl) {
      cl->easy_handle->state.shared_conn = NULL; /* no more shared */
      if(cl->easy_handle->state.closed)
        /* close handle only if curl_easy_cleanup() already has been called
           for this easy handle */
        Curl_close(cl->easy_handle);
      n = cl->next;
      free(cl);
      cl= n;
    }

    Curl_rm_connc(multi->connc);

    /* remove all easy handles */
    easy = multi->easy.next;
    while(easy != &multi->easy) {
      nexteasy=easy->next;
      if(easy->easy_handle->dns.hostcachetype == HCACHE_MULTI) {
        /* clear out the usage of the shared DNS cache */
        easy->easy_handle->dns.hostcache = NULL;
        easy->easy_handle->dns.hostcachetype = HCACHE_NONE;
      }

      /* Clear the pointer to the connection cache */
      easy->easy_handle->state.connc = NULL;

      Curl_easy_addmulti(easy->easy_handle, NULL); /* clear the association */

      if(easy->msg)
        free(easy->msg);
      free(easy);
      easy = nexteasy;
    }

    free(multi);

    return CURLM_OK;
  }
  else
    return CURLM_BAD_HANDLE;
}