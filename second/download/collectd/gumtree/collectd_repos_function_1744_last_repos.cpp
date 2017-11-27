static void ovs_db_reconnect(ovs_db_t *pdb) {
  const char *node_info = pdb->node;
  struct addrinfo *result;

  if (pdb->unix_path[0] != '\0') {
    /* use UNIX socket instead of INET address */
    node_info = pdb->unix_path;
    result = calloc(1, sizeof(struct addrinfo));
    struct sockaddr_un *sa_unix = calloc(1, sizeof(struct sockaddr_un));
    if (result == NULL || sa_unix == NULL) {
      sfree(result);
      sfree(sa_unix);
      return;
    }
    result->ai_family = AF_UNIX;
    result->ai_socktype = SOCK_STREAM;
    result->ai_addrlen = sizeof(*sa_unix);
    result->ai_addr = (struct sockaddr *)sa_unix;
    sa_unix->sun_family = result->ai_family;
    sstrncpy(sa_unix->sun_path, pdb->unix_path, sizeof(sa_unix->sun_path));
  } else {
    /* inet socket address */
    struct addrinfo hints;

    /* setup criteria for selecting the socket address */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    /* get socket addresses */
    int ret = getaddrinfo(pdb->node, pdb->service, &hints, &result);
    if (ret != 0) {
      OVS_ERROR("getaddrinfo(): %s", gai_strerror(ret));
      return;
    }
  }
  /* try to connect to the server */
  for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    char errbuff[OVS_ERROR_BUFF_SIZE];
    int sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock < 0) {
      sstrerror(errno, errbuff, sizeof(errbuff));
      OVS_DEBUG("socket(): %s", errbuff);
      continue;
    }
    if (connect(sock, rp->ai_addr, rp->ai_addrlen) < 0) {
      close(sock);
      sstrerror(errno, errbuff, sizeof(errbuff));
      OVS_DEBUG("connect(): %s [family=%d]", errbuff, rp->ai_family);
    } else {
      /* send notification to event thread */
      ovs_db_event_post(pdb, OVS_DB_EVENT_CONN_ESTABLISHED);
      pdb->sock = sock;
      break;
    }
  }

  if (pdb->sock < 0)
    OVS_ERROR("connect to \"%s\" failed", node_info);

  freeaddrinfo(result);
}