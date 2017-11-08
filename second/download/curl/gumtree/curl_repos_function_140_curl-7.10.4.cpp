static int Store_SSL_Session(struct connectdata *conn)
{
  SSL_SESSION *ssl_sessionid;
  int i;
  struct SessionHandle *data=conn->data; /* the mother of all structs */
  struct curl_ssl_session *store = &data->state.session[0];
  int oldest_age=data->state.session[0].age; /* zero if unused */

  /* ask OpenSSL, say please */

#ifdef HAVE_SSL_GET1_SESSION
  ssl_sessionid = SSL_get1_session(conn->ssl.handle);

  /* SSL_get1_session() will increment the reference
     count and the session will stay in memory until explicitly freed with
     SSL_SESSION_free(3), regardless of its state. 
     This function was introduced in openssl 0.9.5a. */
#else
  ssl_sessionid = SSL_get_session(conn->ssl.handle);

  /* if SSL_get1_session() is unavailable, use SSL_get_session().
     This is an inferior option because the session can be flushed
     at any time by openssl. It is included only so curl compiles
     under versions of openssl < 0.9.5a.
     
     WARNING: How curl behaves if it's session is flushed is
     untested. 
  */
#endif

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
    Kill_Single_Session(store);
  else
    store = &data->state.session[i]; /* use this slot */
  
  /* now init the session struct wisely */
  store->sessionid = ssl_sessionid;
  store->age = data->state.sessionage;      /* set current age */
  store->name = strdup(conn->name);       /* clone host name */
  store->remote_port = conn->remote_port; /* port number */

  Curl_clone_ssl_config(&conn->ssl_config, &store->ssl_config);

  return 0;
}