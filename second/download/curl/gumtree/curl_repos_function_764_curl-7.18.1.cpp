CURLMcode curl_multi_remove_handle(CURLM *multi_handle,
                                   CURL *curl_handle)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;

  /* First, make some basic checks that the CURLM handle is a good handle */
  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  /* Verify that we got a somewhat good easy handle too */
  if(!GOOD_EASY_HANDLE(curl_handle))
    return CURLM_BAD_EASY_HANDLE;

  /* pick-up from the 'curl_handle' the kept position in the list */
  easy = ((struct SessionHandle *)curl_handle)->multi_pos;

  if(easy) {
    bool premature = (bool)(easy->state != CURLM_STATE_COMPLETED);

    /* If the 'state' is not INIT or COMPLETED, we might need to do something
       nice to put the easy_handle in a good known state when this returns. */
    if(premature)
      /* this handle is "alive" so we need to count down the total number of
         alive connections when this is removed */
      multi->num_alive--;

    if(easy->easy_conn &&
        (easy->easy_conn->send_pipe->size +
         easy->easy_conn->recv_pipe->size > 1) &&
        easy->state > CURLM_STATE_WAITDO &&
        easy->state < CURLM_STATE_COMPLETED) {
      /* If the handle is in a pipeline and has started sending off its
         request but not received its reponse yet, we need to close
         connection. */
      easy->easy_conn->bits.close = TRUE;
      /* Set connection owner so that Curl_done() closes it.
         We can sefely do this here since connection is killed. */
      easy->easy_conn->data = easy->easy_handle;
    }

    /* The timer must be shut down before easy->multi is set to NULL,
       else the timenode will remain in the splay tree after
       curl_easy_cleanup is called. */
    Curl_expire(easy->easy_handle, 0);

    if(easy->easy_handle->dns.hostcachetype == HCACHE_MULTI) {
      /* clear out the usage of the shared DNS cache */
      easy->easy_handle->dns.hostcache = NULL;
      easy->easy_handle->dns.hostcachetype = HCACHE_NONE;
    }

    /* we must call Curl_done() here (if we still "own it") so that we don't
       leave a half-baked one around */
    if(easy->easy_conn &&
       (easy->easy_conn->data == easy->easy_handle)) {

      /* Curl_done() clears the conn->data field to lose the association
         between the easy handle and the connection

         Note that this ignores the return code simply because there's nothing
         really useful to do with it anyway! */
      (void)Curl_done(&easy->easy_conn, easy->result, premature);

      if(easy->easy_conn)
        /* the connection is still alive, set back the association to enable
           the check below to trigger TRUE */
        easy->easy_conn->data = easy->easy_handle;
    }

    /* If this easy_handle was the last one in charge for one or more
       connections a the shared connection cache, we might need to keep this
       handle around until either A) the connection is closed and killed
       properly, or B) another easy_handle uses the connection.

       The reason why we need to have a easy_handle associated with a live
       connection is simply that some connections will need a handle to get
       closed down properly. Currently, the only connections that need to keep
       a easy_handle handle around are using FTP(S). Such connections have
       the PROT_CLOSEACTION bit set.

       Thus, we need to check for all connections in the shared cache that
       points to this handle and are using PROT_CLOSEACTION. If there's any,
       we need to add this handle to the list of "easy handles kept around for
       nice connection closures".
     */
    if(multi_conn_using(multi, easy->easy_handle)) {
      /* There's at least one connection using this handle so we must keep
         this handle around. We also keep the connection cache pointer
         pointing to the shared one since that will be used on close as
         well. */
      easy->easy_handle->state.shared_conn = multi;

      /* this handle is still being used by a shared connection cache and
         thus we leave it around for now */
      add_closure(multi, easy->easy_handle);
    }

    if(easy->easy_handle->state.connc->type == CONNCACHE_MULTI) {
      /* if this was using the shared connection cache we clear the pointer
         to that since we're not part of that handle anymore */
      easy->easy_handle->state.connc = NULL;

      /* and modify the connectindex since this handle can't point to the
         connection cache anymore */
      if(easy->easy_conn &&
         (easy->easy_conn->send_pipe->size +
          easy->easy_conn->recv_pipe->size == 0))
        easy->easy_conn->connectindex = -1;
    }

    /* change state without using multistate(), only to make singlesocket() do
       what we want */
    easy->state = CURLM_STATE_COMPLETED;
    singlesocket(multi, easy); /* to let the application know what sockets
                                  that vanish with this handle */

    Curl_easy_addmulti(easy->easy_handle, NULL); /* clear the association
                                                    to this multi handle */

    /* make the previous node point to our next */
    if(easy->prev)
      easy->prev->next = easy->next;
    /* make our next point to our previous node */
    if(easy->next)
      easy->next->prev = easy->prev;

    easy->easy_handle->set.one_easy = NULL; /* detached */

    /* Null the position in the controlling structure */
    easy->easy_handle->multi_pos = NULL;

    /* NOTE NOTE NOTE
       We do not touch the easy handle here! */
    if(easy->msg)
      free(easy->msg);
    free(easy);

    multi->num_easy--; /* one less to care about now */

    update_timer(multi);
    return CURLM_OK;
  }
  else
    return CURLM_BAD_EASY_HANDLE; /* twasn't found */
}