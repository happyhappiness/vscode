static long
ConnectionStore(struct SessionHandle *data,
                struct connectdata *conn)
{
  long i;
  for(i=0; i< data->state.numconnects; i++) {
    if(!data->state.connects[i])
      break;
  }
  if(i == data->state.numconnects) {
    /* there was no room available, kill one */
    i = ConnectionKillOne(data);
    infof(data, "Connection (#%d) was killed to make room\n", i);
  }

  if(-1 != i) {
    /* only do this if a true index was returned, if -1 was returned there
       is no room in the cache for an unknown reason and we cannot store
       this there. */
    data->state.connects[i] = conn; /* fill in this */
    conn->connectindex = i; /* make the child know where the pointer to this
                               particular data is stored */
  }
  return i;
}