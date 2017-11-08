void Curl_expire(struct SessionHandle *data, long milli)
{
  struct Curl_multi *multi = data->multi;
  struct timeval *nowp = &data->state.expiretime;
  int rc;

  /* this is only interesting for multi-interface using libcurl, and only
     while there is still a multi interface struct remaining! */
  if(!multi)
    return;

  if(!milli) {
    /* No timeout, clear the time data. */
    if(nowp->tv_sec) {
      /* Since this is an cleared time, we must remove the previous entry from
         the splay tree */
      rc = Curl_splayremovebyaddr(multi->timetree,
                                  &data->state.timenode,
                                  &multi->timetree);
      if(rc)
        infof(data, "Internal error clearing splay node = %d\n", rc);
      infof(data, "Expire cleared\n");
      nowp->tv_sec = 0;
      nowp->tv_usec = 0;
    }
  }
  else {
    struct timeval set;
    int rest;

    set = Curl_tvnow();
    set.tv_sec += milli/1000;
    set.tv_usec += (milli%1000)*1000;

    rest = (int)(set.tv_usec - 1000000);
    if(rest > 0) {
      /* bigger than a full microsec */
      set.tv_sec++;
      set.tv_usec -= 1000000;
    }

    if(nowp->tv_sec) {
      /* This means that the struct is added as a node in the splay tree.
         Compare if the new time is earlier, and only remove-old/add-new if it
         is. */
      long diff = curlx_tvdiff(set, *nowp);
      if(diff > 0)
        /* the new expire time was later so we don't change this */
        return;

      /* Since this is an updated time, we must remove the previous entry from
         the splay tree first and then re-add the new value */
      rc = Curl_splayremovebyaddr(multi->timetree,
                                  &data->state.timenode,
                                  &multi->timetree);
      if(rc)
        infof(data, "Internal error removing splay node = %d\n", rc);
    }

    *nowp = set;
#if 0
    infof(data, "Expire at %ld / %ld (%ldms)\n",
          (long)nowp->tv_sec, (long)nowp->tv_usec, milli);
#endif
    data->state.timenode.payload = data;
    multi->timetree = Curl_splayinsert((int)nowp->tv_sec,
                                       multi->timetree,
                                       &data->state.timenode);
  }
#if 0
  Curl_splayprint(multi->timetree, 0, TRUE);
#endif
}