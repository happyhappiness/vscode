CURLMcode curl_multi_add_handle(CURLM *multi_handle,
                                CURL *easy_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  struct closure *cl;
  struct closure *prev=NULL;

  /* First, make some basic checks that the CURLM handle is a good handle */
  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  /* Verify that we got a somewhat good easy handle too */
  if(!GOOD_EASY_HANDLE(easy_handle))
    return CURLM_BAD_EASY_HANDLE;

  /* Prevent users to add the same handle more than once! */
  if(((struct SessionHandle *)easy_handle)->multi)
    /* possibly we should create a new unique error code for this condition */
    return CURLM_BAD_EASY_HANDLE;

  /* Now, time to add an easy handle to the multi stack */
  easy = (struct Curl_one_easy *)calloc(sizeof(struct Curl_one_easy), 1);
  if(!easy)
    return CURLM_OUT_OF_MEMORY;

  cl = multi->closure;
  while(cl) {
    struct closure *next = cl->next;
    if(cl->easy_handle == (struct SessionHandle *)easy_handle) {
      /* remove this handle from the closure list */
      free(cl);
      if(prev)
        prev->next = next;
      else
        multi->closure = next;
      break; /* no need to continue since this handle can only be present once
                in the list */
    }
    prev = cl;
    cl = next;
  }

  /* set the easy handle */
  easy->easy_handle = easy_handle;
  multistate(easy, CURLM_STATE_INIT);

  /* set the back pointer to one_easy to assist in removal */
  easy->easy_handle->multi_pos =  easy;

  /* for multi interface connections, we share DNS cache automatically if the
     easy handle's one is currently private. */
  if(easy->easy_handle->dns.hostcache &&
      (easy->easy_handle->dns.hostcachetype == HCACHE_PRIVATE)) {
    Curl_hash_destroy(easy->easy_handle->dns.hostcache);
    easy->easy_handle->dns.hostcache = NULL;
    easy->easy_handle->dns.hostcachetype = HCACHE_NONE;
  }

  if(!easy->easy_handle->dns.hostcache ||
      (easy->easy_handle->dns.hostcachetype == HCACHE_NONE)) {
    easy->easy_handle->dns.hostcache = multi->hostcache;
    easy->easy_handle->dns.hostcachetype = HCACHE_MULTI;
  }

  if(easy->easy_handle->state.connc) {
    if(easy->easy_handle->state.connc->type == CONNCACHE_PRIVATE) {
      /* kill old private version */
      Curl_rm_connc(easy->easy_handle->state.connc);
      /* point out our shared one instead */
      easy->easy_handle->state.connc = multi->connc;
    }
    /* else it is already using multi? */
  }
  else
    /* point out our shared one */
    easy->easy_handle->state.connc = multi->connc;

  /* Make sure the type is setup correctly */
  easy->easy_handle->state.connc->type = CONNCACHE_MULTI;

  /* This adds the new entry at the back of the list
     to try and maintain a FIFO queue so the pipelined
     requests are in order. */

  /* We add this new entry last in the list. We make our 'next' point to the
     'first' struct and our 'prev' point to the previous 'prev' */
  easy->next = &multi->easy;
  easy->prev = multi->easy.prev;

  /* make 'easy' the last node in the chain */
  multi->easy.prev = easy;

  /* if there was a prev node, make sure its 'next' pointer links to
     the new node */
  easy->prev->next = easy;

  Curl_easy_addmulti(easy_handle, multi_handle);

  /* make the SessionHandle struct refer back to this struct */
  easy->easy_handle->set.one_easy = easy;

  /* Set the timeout for this handle to expire really soon so that it will
     be taken care of even when this handle is added in the midst of operation
     when only the curl_multi_socket() API is used. During that flow, only
     sockets that time-out or have actions will be dealt with. Since this
     handle has no action yet, we make sure it times out to get things to
     happen. */
  Curl_expire(easy->easy_handle, 10);

  /* increase the node-counter */
  multi->num_easy++;

  if((multi->num_easy * 4) > multi->connc->num) {
    /* We want the connection cache to have plenty room. Before we supported
       the shared cache every single easy handle had 5 entries in their cache
       by default. */
    long newmax = multi->num_easy * 4;

    if(multi->maxconnects && (multi->maxconnects < newmax))
      /* don't grow beyond the allowed size */
      newmax = multi->maxconnects;

    if(newmax > multi->connc->num) {
      /* we only do this is we can in fact grow the cache */
      CURLcode res = Curl_ch_connc(easy_handle, multi->connc, newmax);
      if(res != CURLE_OK) {
        /* FIXME: may need to do more cleanup here */
        curl_multi_remove_handle(multi_handle, easy_handle);
        return CURLM_OUT_OF_MEMORY;
      }
    }
  }

  /* increase the alive-counter */
  multi->num_alive++;

  update_timer(multi);
  return CURLM_OK;
}