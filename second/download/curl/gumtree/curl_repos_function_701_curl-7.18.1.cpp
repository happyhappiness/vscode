static long
ConnectionStore(struct SessionHandle *data,
                struct connectdata *conn)
{
  long i;
  for(i=0; i< data->state.connc->num; i++) {
    if(!data->state.connc->connects[i])
      break;
  }
  if(i == data->state.connc->num) {
    /* there was no room available, kill one */
    i = ConnectionKillOne(data);
    if(-1 != i)
      infof(data, "Connection (#%d) was killed to make room (holds %d)\n",
            i, data->state.connc->num);
    else
      infof(data, "This connection did not fit in the connection cache\n");
  }

  conn->connectindex = i; /* Make the child know where the pointer to this
                             particular data is stored. But note that this -1
                             if this is not within the cache and this is
                             probably not checked for everywhere (yet). */
  conn->inuse = TRUE;
  if(-1 != i) {
    /* Only do this if a true index was returned, if -1 was returned there
       is no room in the cache for an unknown reason and we cannot store
       this there.

       TODO: make sure we really can work with more handles than positions in
       the cache, or possibly we should (allow to automatically) resize the
       connection cache when we add more easy handles to a multi handle!
    */
    data->state.connc->connects[i] = conn; /* fill in this */
    conn->data = data;
  }

  return i;
}