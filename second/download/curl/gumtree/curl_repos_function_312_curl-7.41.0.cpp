struct berval * *
Curl_ldap_get_values_len_a(void * ld, LDAPMessage * entry, const char * attr)

{
  char * cp;
  struct berval * * result;

  cp = (char *) NULL;

  if(attr) {
    int i = strlen(attr);

    if(!(cp = malloc(i + 1))) {
      ldap_set_lderrno(ld, LDAP_NO_MEMORY, NULL,
                       ldap_err2string(LDAP_NO_MEMORY));
      return (struct berval * *) NULL;
      }

    QadrtConvertA2E(cp, attr, i, i);
    cp[i] = '\0';
    }

  result = ldap_get_values_len(ld, entry, cp);

  if(cp)
    free(cp);

  /* Result data are binary in nature, so they haven't been
     converted to EBCDIC. Therefore do not convert. */

  return result;
}