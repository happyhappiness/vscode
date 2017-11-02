void *
Curl_ldap_init_a(char * host, int port)

{
  unsigned int i;
  char * ehost;
  void * result;

  if(!host)
    return (void *) ldap_init(host, port);

  i = strlen(host);

  if(!(ehost = malloc(i + 1)))
    return (void *) NULL;

  QadrtConvertA2E(ehost, host, i, i);
  ehost[i] = '\0';
  result = (void *) ldap_init(ehost, port);
  free(ehost);
  return result;
}