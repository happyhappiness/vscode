void Curl_expire(struct Curl_easy *data, time_t milli, expire_id id)
{
  struct Curl_multi *multi = data->multi;
  struct curltime *nowp = &data->state.expiretime;
  int rc;
  struct curltime set;

  /* this is only interesting while there is still an associated multi struct
     remaining! */
  if(!multi)
    return;

  DEBUGASSERT(id < EXPIRE_LAST);

  set = Curl_tvnow();
  set.tv_sec += milli/1000;
  set.tv_usec += (unsigned int)(milli%1000)*1000;

  if(set.tv_usec >= 1000000) {
    set.tv_sec++;
    set.tv_usec -= 1000000;
  }

  /* Remove any timer with the same id just in case. */
  multi_deltimeout(data, id);

  /* Add it to the timer list.  It must stay in the list until it has expired
     in case we need to recompute the minimum timer later. */
  multi_addtimeout(data, &set, id);

  if(nowp->tv_sec || nowp->tv_usec) {
    /* This means that the struct is added as a node in the splay tree.
       Compare if the new time is earlier, and only remove-old/add-new if it
       is. */
    time_t diff = curlx_tvdiff(set, *nowp);

    if(diff > 0) {
      /* The current splay tree entry is sooner than this new expiry time.
         We don't need to update our splay tree entry. */
      return;
    }

    /* Since this is an updated time, we must remove the previous entry from
       the splay tree first and then re-add the new value */
    rc = Curl_splayremovebyaddr(multi->timetree,
                                &data->state.timenode,
                                &multi->timetree);
    if(rc)
      infof(data, "Internal error removing splay node = %d\n", rc);
  }

  /* Indicate that we are in the splay tree and insert the new timer expiry
     value since it is our local minimum. */
  *nowp = set;
  data->state.timenode.payload = data;
  multi->timetree = Curl_splayinsert(*nowp, multi->timetree,
                                     &data->state.timenode);
}