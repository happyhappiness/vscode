{
    /* Since this is an cleared time, we must remove the previous entry from
       the splay tree */
    struct curl_llist *list = &data->state.timeoutlist;

    rc = Curl_splayremovebyaddr(multi->timetree,
                                &data->state.timenode,
                                &multi->timetree);
    if(rc)
      infof(data, "Internal error clearing splay node = %d\n", rc);

    /* flush the timeout list too */
    while(list->size > 0) {
      Curl_llist_remove(list, list->tail, NULL);
    }

#ifdef DEBUGBUILD
    infof(data, "Expire cleared\n");
#endif
    nowp->tv_sec = 0;
    nowp->tv_usec = 0;
  }