CURLcode Curl_ldap(struct connectdata *conn, bool *done)
{
  CURLcode status = CURLE_OK;
  int rc = 0;
#ifndef WIN32
  int    (*ldap_url_parse)(char *, LDAPURLDesc **);
  void   (*ldap_free_urldesc)(void *);
#endif
  void  *(__cdecl *ldap_init)(char *, int);
  int    (__cdecl *ldap_simple_bind_s)(void *, char *, char *);
  int    (__cdecl *ldap_unbind_s)(void *);
  int    (__cdecl *ldap_search_s)(void *, char *, int, char *, char **,
                                  int, void **);
  void  *(__cdecl *ldap_first_entry)(void *, void *);
  void  *(__cdecl *ldap_next_entry)(void *, void *);
  char  *(__cdecl *ldap_err2string)(int);
  char  *(__cdecl *ldap_get_dn)(void *, void *);
  char  *(__cdecl *ldap_first_attribute)(void *, void *, void **);
  char  *(__cdecl *ldap_next_attribute)(void *, void *, void *);
  char **(__cdecl *ldap_get_values)(void *, void *, const char *);
  void   (__cdecl *ldap_value_free)(char **);
  void   (__cdecl *ldap_memfree)(void *);
  void   (__cdecl *ber_free)(void *, int);

  void *server;
  LDAPURLDesc *ludp = NULL;
  const char *mod_name;
  void *result;
  void *entryIterator;     /*! type should be 'LDAPMessage *' */
  int num = 0;
  struct SessionHandle *data=conn->data;

  *done = TRUE; /* unconditionally */
  infof(data, "LDAP local: %s\n", data->change.url);

  if (!DynaOpen(&mod_name)) {
    failf(data, "The %s LDAP library/libraries couldn't be opened", mod_name);
    return CURLE_LIBRARY_NOT_FOUND;
  }

  /* The types are needed because ANSI C distinguishes between
   * pointer-to-object (data) and pointer-to-function.
   */
  DYNA_GET_FUNCTION(void *(__cdecl *)(char *, int), ldap_init);
  DYNA_GET_FUNCTION(int (__cdecl *)(void *, char *, char *), ldap_simple_bind_s);
  DYNA_GET_FUNCTION(int (__cdecl *)(void *), ldap_unbind_s);
#ifndef WIN32
  DYNA_GET_FUNCTION(int (*)(char *, LDAPURLDesc **), ldap_url_parse);
  DYNA_GET_FUNCTION(void (*)(void *), ldap_free_urldesc);
#endif
  DYNA_GET_FUNCTION(int (__cdecl *)(void *, char *, int, char *, char **, int,
                            void **), ldap_search_s);
  DYNA_GET_FUNCTION(void *(__cdecl *)(void *, void *), ldap_first_entry);
  DYNA_GET_FUNCTION(void *(__cdecl *)(void *, void *), ldap_next_entry);
  DYNA_GET_FUNCTION(char *(__cdecl *)(int), ldap_err2string);
  DYNA_GET_FUNCTION(char *(__cdecl *)(void *, void *), ldap_get_dn);
  DYNA_GET_FUNCTION(char *(__cdecl *)(void *, void *, void **), ldap_first_attribute);
  DYNA_GET_FUNCTION(char *(__cdecl *)(void *, void *, void *), ldap_next_attribute);
  DYNA_GET_FUNCTION(char **(__cdecl *)(void *, void *, const char *), ldap_get_values);
  DYNA_GET_FUNCTION(void (__cdecl *)(char **), ldap_value_free);
  DYNA_GET_FUNCTION(void (__cdecl *)(void *), ldap_memfree);
  DYNA_GET_FUNCTION(void (__cdecl *)(void *, int), ber_free);

  server = (*ldap_init)(conn->host.name, (int)conn->port);
  if (server == NULL) {
    failf(data, "LDAP local: Cannot connect to %s:%d",
          conn->host.name, conn->port);
    status = CURLE_COULDNT_CONNECT;
    goto quit;
  }

  rc = (*ldap_simple_bind_s)(server,
                             conn->bits.user_passwd ? conn->user : NULL,
                             conn->bits.user_passwd ? conn->passwd : NULL);
  if (rc != 0) {
     failf(data, "LDAP local: %s", (*ldap_err2string)(rc));
     status = CURLE_LDAP_CANNOT_BIND;
     goto quit;
  }

#ifdef WIN32
  rc = _ldap_url_parse(conn, &ludp);
#else
  rc = (*ldap_url_parse)(data->change.url, &ludp);
#endif

  if (rc != 0) {
     failf(data, "LDAP local: %s", (*ldap_err2string)(rc));
     status = CURLE_LDAP_INVALID_URL;
     goto quit;
  }

  rc = (*ldap_search_s)(server, ludp->lud_dn, ludp->lud_scope,
                        ludp->lud_filter, ludp->lud_attrs, 0, &result);

  if (rc != 0 && rc != LDAP_SIZELIMIT_EXCEEDED) {
    failf(data, "LDAP remote: %s", (*ldap_err2string)(rc));
    status = CURLE_LDAP_SEARCH_FAILED;
    goto quit;
  }

  for(num = 0, entryIterator = (*ldap_first_entry)(server, result);
      entryIterator;
      entryIterator = (*ldap_next_entry)(server, entryIterator), num++)
  {
    void  *ber = NULL;      /*! is really 'BerElement **' */
    void  *attribute;       /*! suspicious that this isn't 'const' */
    char  *dn = (*ldap_get_dn)(server, entryIterator);
    int i;

    Curl_client_write(data, CLIENTWRITE_BODY, (char *)"DN: ", 4);
    Curl_client_write(data, CLIENTWRITE_BODY, (char *)dn, 0);
    Curl_client_write(data, CLIENTWRITE_BODY, (char *)"\n", 1);

    for (attribute = (*ldap_first_attribute)(server, entryIterator, &ber);
         attribute;
         attribute = (*ldap_next_attribute)(server, entryIterator, ber))
    {
      char **vals = (*ldap_get_values)(server, entryIterator, attribute);

      if (vals != NULL)
      {
        for (i = 0; (vals[i] != NULL); i++)
        {
          Curl_client_write(data, CLIENTWRITE_BODY, (char *)"\t", 1);
          Curl_client_write(data, CLIENTWRITE_BODY, (char*) attribute, 0);
          Curl_client_write(data, CLIENTWRITE_BODY, (char *)": ", 2);
          Curl_client_write(data, CLIENTWRITE_BODY, vals[i], 0);
          Curl_client_write(data, CLIENTWRITE_BODY, (char *)"\n", 0);
        }

        /* Free memory used to store values */
        (*ldap_value_free)(vals);
      }
      Curl_client_write(data, CLIENTWRITE_BODY, (char *)"\n", 1);

      (*ldap_memfree)(attribute);
    }
    (*ldap_memfree)(dn);
    if (ber)
       (*ber_free)(ber, 0);
  }

quit:
  LDAP_TRACE (("Received %d entries\n", num));
  if (rc == LDAP_SIZELIMIT_EXCEEDED)
     infof(data, "There are more than %d entries\n", num);
  if (ludp)
     (*ldap_free_urldesc)(ludp);
  if (server)
     (*ldap_unbind_s)(server);

  DynaClose();

  /* no data to transfer */
  Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  conn->bits.close = TRUE;

  return status;
}