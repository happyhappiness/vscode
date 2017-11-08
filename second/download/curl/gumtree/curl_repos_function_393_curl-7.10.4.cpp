CURLcode Curl_ldap(struct connectdata *conn)
{
  CURLcode status = CURLE_OK;
  int rc;
  void *(*ldap_open)(char *, int);
  int (*ldap_simple_bind_s)(void *, char *, char *);
  int (*ldap_unbind_s)(void *);
  int (*ldap_url_search_s)(void *, char *, int, void **);
  void *(*ldap_first_entry)(void *, void *);
  void *(*ldap_next_entry)(void *, void *);
  char *(*ldap_err2string)(int);
  int (*ldap_entry2text)(void *, char *, void *, void *, char **, char **, int (*)(void *, char *, int), void *, char *, int, unsigned long);
  int (*ldap_entry2html)(void *, char *, void *, void *, char **, char **, int (*)(void *, char *, int), void *, char *, int, unsigned long, char *, char *);
  void *server;
  void *result;
  void *entryIterator;

  int ldaptext;
  struct SessionHandle *data=conn->data;
  
  infof(data, "LDAP: %s\n", data->change.url);

  DynaOpen();
  if (libldap == NULL) {
    failf(data, "The needed LDAP library/libraries couldn't be opened");
    return CURLE_LIBRARY_NOT_FOUND;
  }

  ldaptext = data->set.ftp_ascii; /* This is a dirty hack */
  
  /* The types are needed because ANSI C distinguishes between
   * pointer-to-object (data) and pointer-to-function.
   */
  DYNA_GET_FUNCTION(void *(*)(char *, int), ldap_open);
  DYNA_GET_FUNCTION(int (*)(void *, char *, char *), ldap_simple_bind_s);
  DYNA_GET_FUNCTION(int (*)(void *), ldap_unbind_s);
  DYNA_GET_FUNCTION(int (*)(void *, char *, int, void **), ldap_url_search_s);
  DYNA_GET_FUNCTION(void *(*)(void *, void *), ldap_first_entry);
  DYNA_GET_FUNCTION(void *(*)(void *, void *), ldap_next_entry);
  DYNA_GET_FUNCTION(char *(*)(int), ldap_err2string);
  DYNA_GET_FUNCTION(int (*)(void *, char *, void *, void *, char **, char **, int (*)(void *, char *, int), void *, char *, int, unsigned long), ldap_entry2text);
  DYNA_GET_FUNCTION(int (*)(void *, char *, void *, void *, char **, char **, int (*)(void *, char *, int), void *, char *, int, unsigned long, char *, char *), ldap_entry2html);
  
  server = ldap_open(conn->hostname, conn->port);
  if (server == NULL) {
    failf(data, "LDAP: Cannot connect to %s:%d",
	  conn->hostname, conn->port);
    status = CURLE_COULDNT_CONNECT;
  } else {
    rc = ldap_simple_bind_s(server,
                            conn->bits.user_passwd?data->state.user:NULL,
                            conn->bits.user_passwd?data->state.passwd:NULL);
    if (rc != 0) {
      failf(data, "LDAP: %s", ldap_err2string(rc));
      status = CURLE_LDAP_CANNOT_BIND;
    } else {
      rc = ldap_url_search_s(server, data->change.url, 0, &result);
      if (rc != 0) {
	failf(data, "LDAP: %s", ldap_err2string(rc));
	status = CURLE_LDAP_SEARCH_FAILED;
      } else {
	for (entryIterator = ldap_first_entry(server, result);
	     entryIterator;
	     entryIterator = ldap_next_entry(server, entryIterator))
	  {
	    if (ldaptext) {
	      rc = ldap_entry2text(server, NULL, entryIterator, NULL,
				   NULL, NULL, WriteProc, data,
				   (char *)"", 0, 0);
	      if (rc != 0) {
		failf(data, "LDAP: %s", ldap_err2string(rc));
		status = CURLE_LDAP_SEARCH_FAILED;
	      }
	    } else {
	      rc = ldap_entry2html(server, NULL, entryIterator, NULL,
				   NULL, NULL, WriteProc, data,
				   (char *)"", 0, 0, NULL, NULL);
	      if (rc != 0) {
		failf(data, "LDAP: %s", ldap_err2string(rc));
		status = CURLE_LDAP_SEARCH_FAILED;
	      }
	    }
	  }
      }
      ldap_unbind_s(server);
    }
  }
  DynaClose();

  /* no data to transfer */
  Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  
  return status;
}