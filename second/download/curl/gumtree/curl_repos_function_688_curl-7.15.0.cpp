CURLcode Curl_ssl_addsessionid(struct connectdata *conn,
                               void *ssl_sessionid,
                               size_t idsize)
{
  int i;
  struct SessionHandle *data=conn->data; /* the mother of all structs */
  struct curl_ssl_session *store = &data->state.session[0];
  long oldest_age=data->state.session[0].age; /* zero if unused */
  char *clone_host;

  clone_host = strdup(conn->host.name);
  if(!clone_host)
    return CURLE_OUT_OF_MEMORY; /* bail out */

  /* Now we should add the session ID and the host name to the cache, (remove
     the oldest if necessary) */

  /* find an empty slot for us, or find the oldest */
  for(i=1; (i<data->set.ssl.numsessions) &&
        data->state.session[i].sessionid; i++) {
    if(data->state.session[i].age < oldest_age) {
      oldest_age = data->state.session[i].age;
      store = &data->state.session[i];
    }
  }
  if(i == data->set.ssl.numsessions)
    /* cache is full, we must "kill" the oldest entry! */
    kill_session(store);
  else
    store = &data->state.session[i]; /* use this slot */

  /* now init the session struct wisely */
  store->sessionid = ssl_sessionid;
  store->idsize = idsize;
  store->age = data->state.sessionage;    /* set current age */
  store->name = clone_host;               /* clone host name */
  store->remote_port = conn->remote_port; /* port number */

  if (!Curl_clone_ssl_config(&conn->ssl_config, &store->ssl_config))
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}