int
Curl_getaddrinfo_a(const char * nodename, const char * servname,
            const struct addrinfo * hints,
            struct addrinfo * * res)

{
  char * enodename;
  char * eservname;
  int status;
  int i;

  enodename = (char *) NULL;
  eservname = (char *) NULL;

  if(nodename) {
    i = strlen(nodename);

    if(!(enodename = malloc(i + 1)))
      return EAI_MEMORY;

    i = QadrtConvertA2E(enodename, nodename, i, i);
    enodename[i] = '\0';
    }

  if(servname) {
    i = strlen(servname);

    if(!(eservname = malloc(i + 1))) {
      if(enodename)
        free(enodename);

      return EAI_MEMORY;
      }

    QadrtConvertA2E(eservname, servname, i, i);
    eservname[i] = '\0';
    }

  status = getaddrinfo(enodename, eservname, hints, res);

  if(enodename)
    free(enodename);

  if(eservname)
    free(eservname);

  return status;
}