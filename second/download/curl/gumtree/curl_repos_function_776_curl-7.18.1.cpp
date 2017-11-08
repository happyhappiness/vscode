static void singlesocket(struct Curl_multi *multi,
                         struct Curl_one_easy *easy)
{
  curl_socket_t socks[MAX_SOCKSPEREASYHANDLE];
  int i;
  struct Curl_sh_entry *entry;
  curl_socket_t s;
  int num;
  unsigned int curraction;

  memset(&socks, 0, sizeof(socks));
  for(i=0; i< MAX_SOCKSPEREASYHANDLE; i++)
    socks[i] = CURL_SOCKET_BAD;

  /* Fill in the 'current' struct with the state as it is now: what sockets to
     supervise and for what actions */
  curraction = multi_getsock(easy, socks, MAX_SOCKSPEREASYHANDLE);

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
      entry = sh_addentry(multi->sockhash, s, easy->easy_handle);
      if(!entry)
        /* fatal */
        return;
    }

    multi->socket_cb(easy->easy_handle,
                     s,
                     action,
                     multi->socket_userp,
                     entry ? entry->socketp : NULL);

    entry->action = action; /* store the current action state */
  }

  num = i; /* number of sockets */

  /* when we've walked over all the sockets we should have right now, we must
     make sure to detect sockets that are removed */
  for(i=0; i< easy->numsocks; i++) {
    int j;
    s = easy->sockets[i];
    for(j=0; j<num; j++) {
      if(s == socks[j]) {
        /* this is still supervised */
        s = CURL_SOCKET_BAD;
        break;
      }
    }
    if(s != CURL_SOCKET_BAD) {
      /* this socket has been removed. Remove it */

      entry = Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(s));
      if(entry) {
        /* just a precaution, this socket really SHOULD be in the hash already
           but in case it isn't, we don't have to tell the app to remove it
           either since it never got to know about it */
        multi->socket_cb(easy->easy_handle,
                         s,
                         CURL_POLL_REMOVE,
                         multi->socket_userp,
                         entry ? entry->socketp : NULL);

        sh_delentry(multi->sockhash, s);
      }
    }
  }

  memcpy(easy->sockets, socks, num*sizeof(curl_socket_t));
  easy->numsocks = num;
}