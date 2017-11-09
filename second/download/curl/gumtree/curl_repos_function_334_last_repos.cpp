int
Curl_ldap_simple_bind_s_a(void * ld, char * dn, char * passwd)

{
  int i;
  char * edn;
  char * epasswd;

  edn = (char *) NULL;
  epasswd = (char *) NULL;

  if(dn) {
    i = strlen(dn);

    if(!(edn = malloc(i + 1)))
      return LDAP_NO_MEMORY;

    QadrtConvertA2E(edn, dn, i, i);
    edn[i] = '\0';
    }

  if(passwd) {
    i = strlen(passwd);

    if(!(epasswd = malloc(i + 1))) {
      free(edn);
      return LDAP_NO_MEMORY;
      }

    QadrtConvertA2E(epasswd, passwd, i, i);
    epasswd[i] = '\0';
    }

  i = ldap_simple_bind_s(ld, edn, epasswd);
  free(epasswd);
  free(edn);
  return i;
}