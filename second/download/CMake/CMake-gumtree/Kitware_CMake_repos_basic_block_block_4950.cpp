{
  struct Curl_multi *multi = data->multi;
  struct timeval *nowp = &data->state.expiretime;
  int rc;
  struct timeval set;

  /* this is only interesting while there is still an associated multi struct
     remaining! */
  if(!multi)
    return;

  DEBUGASSERT(id < EXPIRE_LAST);

  set = Curl_tvnow();
  set.tv_sec += (long)(milli/1000);
  set.tv_usec += (long)(milli%1000)*1000;

  if(set.tv_usec >= 1000000) {
    set.tv_sec++;
    set.tv_usec -= 1000000;
  }

  if(nowp->tv_sec || nowp->tv_usec) {
    /* This means that the struct is added as a node in the splay tree.
       Compare if the new time is earlier, and only remove-old/add-new if it
       is. */
    time_t diff = curlx_tvdiff(set, *nowp);

    /* remove the previous timer first, if there */
    multi_deltimeout(data, id);

    if(diff > 0) {
      /* the new expire time was later so just add it to the queue
         and get out */
      multi_addtimeout(data, &set, id);
      return;
    }

    /* the new time is newer than the presently set one, so add the current
       to the queue and update the head */
    multi_addtimeout(data, nowp, id);

    /* Since this is an updated time, we must remove the previous entry from
       the splay tree first and then re-add the new value */
    rc = Curl_splayremovebyaddr(multi->timetree,
                                &data->state.timenode,
                                &multi->timetree);
    if(rc)
      infof(data, "Internal error removing splay node = %d\n", rc);
  }

  *nowp = set;
  data->state.timenode.payload = data;
  multi->timetree = Curl_splayinsert(*nowp, multi->timetree,
                                     &data->state.timenode);
}