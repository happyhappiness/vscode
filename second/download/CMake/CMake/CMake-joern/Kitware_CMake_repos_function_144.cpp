static CURLcode ldap_connect(struct connectdata *conn, bool *done)
{
  ldapconninfo *li = conn->proto.generic;
  struct Curl_easy *data = conn->data;
  int rc, proto = LDAP_VERSION3;
  char hosturl[1024];
  char *ptr;

  (void)done;

  strcpy(hosturl, "ldap");
  ptr = hosturl+4;
  if(conn->handler->flags & PROTOPT_SSL)
    *ptr++ = 's';
  snprintf(ptr, sizeof(hosturl)-(ptr-hosturl), "://%s:%d",
    conn->host.name, conn->remote_port);

  rc = ldap_init_fd(conn->sock[FIRSTSOCKET], li->proto, hosturl, &li->ld);
  if(rc) {
    failf(data, "LDAP local: Cannot connect to %s, %s",
          hosturl, ldap_err2string(rc));
    return CURLE_COULDNT_CONNECT;
  }

  ldap_set_option(li->ld, LDAP_OPT_PROTOCOL_VERSION, &proto);

#ifdef USE_SSL
  if(conn->handler->flags & PROTOPT_SSL) {
    CURLcode result;
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &li->ssldone);
    if(result)
      return result;
  }
#endif

  return CURLE_OK;
}