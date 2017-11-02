int
Curl_getnameinfo_a(const struct sockaddr * sa, curl_socklen_t salen,
              char * nodename, curl_socklen_t nodenamelen,
              char * servname, curl_socklen_t servnamelen,
              int flags)

{
  char * enodename;
  char * eservname;
  int status;
  int i;

  enodename = (char *) NULL;
  eservname = (char *) NULL;

  if(nodename && nodenamelen)
    if(!(enodename = malloc(nodenamelen)))
      return EAI_MEMORY;

  if(servname && servnamelen)
    if(!(eservname = malloc(servnamelen))) {
      if(enodename)
        free(enodename);

      return EAI_MEMORY;
      }

  status = getnameinfo(sa, salen, enodename, nodenamelen,
                       eservname, servnamelen, flags);

  if(!status) {
    if(enodename) {
      i = QadrtConvertE2A(nodename, enodename,
        nodenamelen - 1, strlen(enodename));
      nodename[i] = '\0';
      }

    if(eservname) {
      i = QadrtConvertE2A(servname, eservname,
        servnamelen - 1, strlen(eservname));
      servname[i] = '\0';
      }
    }

  if(enodename)
    free(enodename);

  if(eservname)
    free(eservname);

  return status;
}