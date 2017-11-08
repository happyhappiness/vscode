CURLcode Curl_ch_connc(struct SessionHandle *data,
                       struct conncache *c,
                       long newamount)
{
  long i;
  struct connectdata **newptr;

  if(newamount < 1)
    newamount = 1; /* we better have at least one entry */

  if(!c) {
    /* we get a NULL pointer passed in as connection cache, which means that
       there is no cache created for this SessionHandle just yet, we create a
       brand new with the requested size.
    */
    data->state.connc = Curl_mk_connc(CONNCACHE_PRIVATE, newamount);
    if(!data->state.connc)
      return CURLE_OUT_OF_MEMORY;
    return CURLE_OK;
  }

  if(newamount < c->num) {
    /* Since this number is *decreased* from the existing number, we must
       close the possibly open connections that live on the indexes that
       are being removed!

       NOTE: for conncache_multi cases we must make sure that we only
       close handles not in use.
    */
    for(i=newamount; i< c->num; i++)
      Curl_disconnect(c->connects[i]);

    /* If the most recent connection is no longer valid, mark it
       invalid. */
    if(data->state.lastconnect <= newamount)
      data->state.lastconnect = -1;
  }
  if(newamount > 0) {
    newptr= (struct connectdata **)
      realloc(c->connects, sizeof(struct connectdata *) * newamount);
    if(!newptr)
      /* we closed a few connections in vain, but so what? */
      return CURLE_OUT_OF_MEMORY;

    /* nullify the newly added pointers */
    for(i=c->num; i<newamount; i++)
      newptr[i] = NULL;

    c->connects = newptr;
    c->num = newamount;
  }
  /* we no longer support less than 1 as size for the connection cache, and
     I'm not sure it ever worked to set it to zero */
  return CURLE_OK;
}