int
Curl_ldap_search_s_a(void * ld, char * base, int scope, char * filter,
                     char * * attrs, int attrsonly, LDAPMessage * * res)

{
  int i;
  int j;
  char * ebase;
  char * efilter;
  char * * eattrs;
  int status;

  ebase = (char *) NULL;
  efilter = (char *) NULL;
  eattrs = (char * *) NULL;
  status = LDAP_SUCCESS;

  if(base) {
    i = strlen(base);

    if(!(ebase = malloc(i + 1)))
      status = LDAP_NO_MEMORY;
    else {
      QadrtConvertA2E(ebase, base, i, i);
      ebase[i] = '\0';
      }
    }

  if(filter && status == LDAP_SUCCESS) {
    i = strlen(filter);

    if(!(efilter = malloc(i + 1)))
      status = LDAP_NO_MEMORY;
    else {
      QadrtConvertA2E(efilter, filter, i, i);
      efilter[i] = '\0';
      }
    }

  if(attrs && status == LDAP_SUCCESS) {
    for(i = 0; attrs[i++];)
      ;

    if(!(eattrs = calloc(i, sizeof *eattrs)))
      status = LDAP_NO_MEMORY;
    else {
      for(j = 0; attrs[j]; j++) {
        i = strlen(attrs[j]);

        if(!(eattrs[j] = malloc(i + 1))) {
          status = LDAP_NO_MEMORY;
          break;
          }

        QadrtConvertA2E(eattrs[j], attrs[j], i, i);
        eattrs[j][i] = '\0';
        }
      }
    }

  if(status == LDAP_SUCCESS)
    status = ldap_search_s(ld, ebase? ebase: "", scope,
                           efilter? efilter: "(objectclass=*)",
                           eattrs, attrsonly, res);

  if(eattrs) {
    for(j = 0; eattrs[j]; j++)
      free(eattrs[j]);

    free(eattrs);
    }

  free(efilter);
  free(ebase);
  return status;
}