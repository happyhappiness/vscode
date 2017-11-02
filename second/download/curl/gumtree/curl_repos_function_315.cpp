char *
Curl_ldap_first_attribute_a(void * ld,
                            LDAPMessage * entry, BerElement * * berptr)

{
  int i;
  char * cp;
  char * cp2;

  cp = ldap_first_attribute(ld, entry, berptr);

  if(!cp)
    return cp;

  i = strlen(cp);

  if(!(cp2 = malloc(i + 1)))
    return cp2;

  QadrtConvertE2A(cp2, cp, i, i);
  cp2[i] = '\0';

  /* No way to allocate a buffer here, because it will be released by
     ldap_memfree() and ldap_memalloc() does not exist. The solution is to
     overwrite the EBCDIC buffer with ASCII to return it. */

  strcpy(cp, cp2);
  free(cp2);
  return cp;
}