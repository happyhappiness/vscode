static bool
ConnectionExists(struct SessionHandle *data,
                 struct connectdata *needle,
                 struct connectdata **usethis)
{
  long i;
  struct connectdata *check;

  for(i=0; i< data->state.numconnects; i++) {
    /*
     * Note that if we use a HTTP proxy, we check connections to that
     * proxy and not to the actual remote server.
     */
    check = data->state.connects[i];
    if(!check)
      /* NULL pointer means not filled-in entry */
      continue;
    if(!needle->bits.httpproxy) {
      /* The requested connection does not use a HTTP proxy */

      if(strequal(needle->protostr, check->protostr) &&
         strequal(needle->name, check->name) &&
         (needle->remote_port == check->remote_port) ) {
        bool dead;
        if(strequal(needle->protostr, "FTP")) {
          /* This is FTP, verify that we're using the same name and
             password as well */
          if(!strequal(needle->data->state.user, check->proto.ftp->user) ||
             !strequal(needle->data->state.passwd, check->proto.ftp->passwd)) {
            /* one of them was different */
            continue;
          }
        }
        dead = SocketIsDead(check->firstsocket);
        if(dead) {
          infof(data, "Connection %d seems to be dead!\n", i);
          Curl_disconnect(check); /* disconnect resources */
          data->state.connects[i]=NULL; /* nothing here */
          continue; /* try another one now */
        }

        *usethis = check;
        return TRUE; /* yes, we found one to use! */
        
      }
    }
    else { /* The requested needle connection is using a proxy,
              is the checked one using the same? */
      if(check->bits.httpproxy &&
         strequal(needle->proxyhost, check->proxyhost) &&
         needle->port == check->port) {
        /* This is the same proxy connection, use it! */
        *usethis = check;
        return TRUE;
      }
    }
  }
  return FALSE; /* no matching connecting exists */
}