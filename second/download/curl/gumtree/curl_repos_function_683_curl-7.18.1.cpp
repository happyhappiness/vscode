CURLcode Curl_close(struct SessionHandle *data)
{
  struct Curl_multi *m = data->multi;

#ifdef CURLDEBUG
  /* only for debugging, scan through all connections and see if there's a
     pipe reference still identifying this handle */

  if(data->state.connc && data->state.connc->type == CONNCACHE_MULTI) {
    struct conncache *c = data->state.connc;
    long i;
    struct curl_llist *pipeline;
    struct curl_llist_element *curr;
    struct connectdata *connptr;

    for(i=0; i< c->num; i++) {
      connptr = c->connects[i];
      if(!connptr)
        continue;

      pipeline = connptr->send_pipe;
      if(pipeline) {
        for (curr = pipeline->head; curr; curr=curr->next) {
          if(data == (struct SessionHandle *) curr->ptr) {
            fprintf(stderr,
                    "MAJOR problem we %p are still in send pipe for %p done %d\n",
                    data, connptr, connptr->bits.done);
          }
        }
      }
      pipeline = connptr->recv_pipe;
      if(pipeline) {
        for (curr = pipeline->head; curr; curr=curr->next) {
          if(data == (struct SessionHandle *) curr->ptr) {
            fprintf(stderr,
                    "MAJOR problem we %p are still in recv pipe for %p done %d\n",
                    data, connptr, connptr->bits.done);
          }
        }
      }
      pipeline = connptr->pend_pipe;
      if(pipeline) {
        for (curr = pipeline->head; curr; curr=curr->next) {
          if(data == (struct SessionHandle *) curr->ptr) {
            fprintf(stderr,
                    "MAJOR problem we %p are still in pend pipe for %p done %d\n",
                    data, connptr, connptr->bits.done);
          }
        }
      }
    }
  }
#endif

  if(m)
    /* This handle is still part of a multi handle, take care of this first
       and detach this handle from there. */
    Curl_multi_rmeasy(data->multi, data);

  data->magic = 0; /* force a clear AFTER the possibly enforced removal from
                      the multi handle, since that function uses the magic
                      field! */

  if(data->state.connc) {

    if(data->state.connc->type == CONNCACHE_PRIVATE) {
      /* close all connections still alive that are in the private connection
         cache, as we no longer have the pointer left to the shared one. */
      close_connections(data);

      /* free the connection cache if allocated privately */
      Curl_rm_connc(data->state.connc);
    }
  }

  if(data->state.shared_conn) {
    /* marked to be used by a pending connection so we can't kill this handle
       just yet */
    data->state.closed = TRUE;
    return CURLE_OK;
  }

  if(data->dns.hostcachetype == HCACHE_PRIVATE)
    Curl_hash_destroy(data->dns.hostcache);

  if(data->state.rangestringalloc)
    free(data->state.range);

  /* Free the pathbuffer */
  Curl_safefree(data->state.pathbuffer);
  Curl_safefree(data->state.proto.generic);

  /* Close down all open SSL info and sessions */
  Curl_ssl_close_all(data);
  Curl_safefree(data->state.first_host);
  Curl_safefree(data->state.scratch);

  if(data->change.referer_alloc)
    free(data->change.referer);

  if(data->change.url_alloc)
    free(data->change.url);

  Curl_safefree(data->state.headerbuff);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  flush_cookies(data, 1);
#endif

  Curl_digest_cleanup(data);

  Curl_safefree(data->info.contenttype);

  /* this destroys the channel and we cannot use it anymore after this */
  ares_destroy(data->state.areschannel);

#if defined(CURL_DOES_CONVERSIONS) && defined(HAVE_ICONV)
  /* close iconv conversion descriptors */
  if(data->inbound_cd != (iconv_t)-1) {
     iconv_close(data->inbound_cd);
  }
  if(data->outbound_cd != (iconv_t)-1) {
     iconv_close(data->outbound_cd);
  }
  if(data->utf8_cd != (iconv_t)-1) {
     iconv_close(data->utf8_cd);
  }
#endif /* CURL_DOES_CONVERSIONS && HAVE_ICONV */

  /* No longer a dirty share, if it exists */
  if(data->share) {
    Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);
    data->share->dirty--;
    Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
  }

  Curl_freeset(data);
  free(data);
  return CURLE_OK;
}