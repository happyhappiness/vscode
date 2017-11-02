static void singlesocket(struct Curl_multi *multi,
                         struct SessionHandle *data)
{
  curl_socket_t socks[MAX_SOCKSPEREASYHANDLE];
  int i;
  struct Curl_sh_entry *entry;
  curl_socket_t s;
  int num;
  unsigned int curraction;
  bool remove_sock_from_hash;

  for(i=0; i< MAX_SOCKSPEREASYHANDLE; i++)
    socks[i] = CURL_SOCKET_BAD;

  /* Fill in the 'current' struct with the state as it is now: what sockets to
     supervise and for what actions */
  curraction = multi_getsock(data, socks, MAX_SOCKSPEREASYHANDLE);

  /* We have 0 .. N sockets already and we get to know about the 0 .. M
     sockets we should have from now on. Detect the differences, remove no
     longer supervised ones and add new ones */

  /* walk over the sockets we got right now */
  for(i=0; (i< MAX_SOCKSPEREASYHANDLE) &&
        (curraction & (GETSOCK_READSOCK(i) | GETSOCK_WRITESOCK(i)));
      i++) {
    int action = CURL_POLL_NONE;

    s = socks[i];

    /* get it from the hash */
    entry = Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(s));

    if(curraction & GETSOCK_READSOCK(i))
      action |= CURL_POLL_IN;
    if(curraction & GETSOCK_WRITESOCK(i))
      action |= CURL_POLL_OUT;

    if(entry) {
      /* yeps, already present so check if it has the same action set */
      if(entry->action == action)
        /* same, continue */
        continue;
    }
    else {
      /* this is a socket we didn't have before, add it! */
      entry = sh_addentry(multi->sockhash, s, data);
      if(!entry)
        /* fatal */
        return;
    }

    /* we know (entry != NULL) at this point, see the logic above */
    if(multi->socket_cb)
      multi->socket_cb(data,
                       s,
                       action,
                       multi->socket_userp,
                       entry->socketp);

    entry->action = action; /* store the current action state */
  }

  num = i; /* number of sockets */

  /* when we've walked over all the sockets we should have right now, we must
     make sure to detect sockets that are removed */
  for(i=0; i< data->numsocks; i++) {
    int j;
    s = data->sockets[i];
    for(j=0; j<num; j++) {
      if(s == socks[j]) {
        /* this is still supervised */
        s = CURL_SOCKET_BAD;
        break;
      }
    }
    if(s != CURL_SOCKET_BAD) {

      /* this socket has been removed. Tell the app to remove it */
      remove_sock_from_hash = TRUE;

      entry = Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(s));
      if(entry) {
        /* check if the socket to be removed serves a connection which has
           other easy-s in a pipeline. In this case the socket should not be
           removed. */
        struct connectdata *easy_conn = data->easy_conn;
        if(easy_conn) {
          if(easy_conn->recv_pipe && easy_conn->recv_pipe->size > 1) {
            /* the handle should not be removed from the pipe yet */
            remove_sock_from_hash = FALSE;

            /* Update the sockhash entry to instead point to the next in line
               for the recv_pipe, or the first (in case this particular easy
               isn't already) */
            if(entry->easy == data) {
              if(isHandleAtHead(data, easy_conn->recv_pipe))
                entry->easy = easy_conn->recv_pipe->head->next->ptr;
              else
                entry->easy = easy_conn->recv_pipe->head->ptr;
            }
          }
          if(easy_conn->send_pipe  && easy_conn->send_pipe->size > 1) {
            /* the handle should not be removed from the pipe yet */
            remove_sock_from_hash = FALSE;

            /* Update the sockhash entry to instead point to the next in line
               for the send_pipe, or the first (in case this particular easy
               isn't already) */
            if(entry->easy == data) {
              if(isHandleAtHead(data, easy_conn->send_pipe))
                entry->easy = easy_conn->send_pipe->head->next->ptr;
              else
                entry->easy = easy_conn->send_pipe->head->ptr;
            }
          }
          /* Don't worry about overwriting recv_pipe head with send_pipe_head,
             when action will be asked on the socket (see multi_socket()), the
             head of the correct pipe will be taken according to the
             action. */
        }
      }
      else
        /* just a precaution, this socket really SHOULD be in the hash already
           but in case it isn't, we don't have to tell the app to remove it
           either since it never got to know about it */
        remove_sock_from_hash = FALSE;

      if(remove_sock_from_hash) {
        /* in this case 'entry' is always non-NULL */
        if(multi->socket_cb)
          multi->socket_cb(data,
                           s,
                           CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);
        sh_delentry(multi->sockhash, s);
      }

    }
  }

  memcpy(data->sockets, socks, num*sizeof(curl_socket_t));
  data->numsocks = num;
}