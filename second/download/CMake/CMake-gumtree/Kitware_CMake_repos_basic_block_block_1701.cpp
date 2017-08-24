{
  // in the event of absolute failure return localhost.
  fqdn = "localhost";

#if defined(_WIN32)
  int ierr;
  // TODO - a more robust implementation for windows, see comments
  // in unix implementation.
  WSADATA wsaData;
  WORD ver = MAKEWORD(2, 0);
  ierr = WSAStartup(ver, &wsaData);
  if (ierr) {
    return -1;
  }

  char base[256] = { '\0' };
  ierr = gethostname(base, 256);
  if (ierr) {
    WSACleanup();
    return -2;
  }
  fqdn = base;

  HOSTENT* hent = gethostbyname(base);
  if (hent) {
    fqdn = hent->h_name;
  }

  WSACleanup();
  return 0;

#elif defined(KWSYS_SYSTEMINFORMATION_IMPLEMENT_FQDN)
  // gethostname typical returns an alias for loopback interface
  // we want the fully qualified domain name. Because there are
  // any number of interfaces on this system we look for the
  // first of these that contains the name returned by gethostname
  // and is longer. failing that we return gethostname and indicate
  // with a failure code. Return of a failure code is not necessarilly
  // an indication of an error. for instance gethostname may return
  // the fully qualified domain name, or there may not be one if the
  // system lives on a private network such as in the case of a cluster
  // node.

  int ierr = 0;
  char base[NI_MAXHOST];
  ierr = gethostname(base, NI_MAXHOST);
  if (ierr) {
    return -1;
  }
  size_t baseSize = strlen(base);
  fqdn = base;

  struct ifaddrs* ifas;
  struct ifaddrs* ifa;
  ierr = getifaddrs(&ifas);
  if (ierr) {
    return -2;
  }

  for (ifa = ifas; ifa != NULL; ifa = ifa->ifa_next) {
    int fam = ifa->ifa_addr ? ifa->ifa_addr->sa_family : -1;
    // Skip Loopback interfaces
    if (((fam == AF_INET) || (fam == AF_INET6)) &&
        !(ifa->ifa_flags & IFF_LOOPBACK)) {
      char host[NI_MAXHOST] = { '\0' };

      const size_t addrlen = (fam == AF_INET ? sizeof(struct sockaddr_in)
                                             : sizeof(struct sockaddr_in6));

      ierr = getnameinfo(ifa->ifa_addr, static_cast<socklen_t>(addrlen), host,
                         NI_MAXHOST, NULL, 0, NI_NAMEREQD);
      if (ierr) {
        // don't report the failure now since we may succeed on another
        // interface. If all attempts fail then return the failure code.
        ierr = -3;
        continue;
      }

      std::string candidate = host;
      if ((candidate.find(base) != std::string::npos) &&
          baseSize < candidate.size()) {
        // success, stop now.
        ierr = 0;
        fqdn = candidate;
        break;
      }
    }
  }
  freeifaddrs(ifas);

  return ierr;
#else
  /* TODO: Implement on more platforms.  */
  fqdn = this->GetHostname();
  return -1;
#endif
}