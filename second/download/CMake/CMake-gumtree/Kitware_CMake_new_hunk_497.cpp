}

if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
                          unsigned int remote_scope_id, const char *interf,
                          char *buf, int buf_size)
{
  struct ifaddrs *iface, *head;
  if2ip_result_t res = IF2IP_NOT_FOUND;

#ifndef ENABLE_IPV6
  (void) remote_scope;

#ifndef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
  (void) remote_scope_id;
#endif

#endif

  if(getifaddrs(&head) >= 0) {
    for(iface = head; iface != NULL; iface=iface->ifa_next) {
      if(iface->ifa_addr != NULL) {
        if(iface->ifa_addr->sa_family == af) {
          if(curl_strequal(iface->ifa_name, interf)) {
            void *addr;
            char *ip;
            char scope[12] = "";
            char ipstr[64];
#ifdef ENABLE_IPV6
            if(af == AF_INET6) {
              unsigned int scopeid = 0;
              unsigned int ifscope = Curl_ipv6_scope(iface->ifa_addr);

              if(ifscope != remote_scope) {
                /* We are interested only in interface addresses whose
                   scope matches the remote address we want to
                   connect to: global for global, link-local for
                   link-local, etc... */
                if(res == IF2IP_NOT_FOUND) res = IF2IP_AF_NOT_SUPPORTED;
                continue;
              }

              addr = &((struct sockaddr_in6 *)iface->ifa_addr)->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
              /* Include the scope of this interface as part of the address */
              scopeid =
                ((struct sockaddr_in6 *)iface->ifa_addr)->sin6_scope_id;

              /* If given, scope id should match. */
              if(remote_scope_id && scopeid != remote_scope_id) {
                if(res == IF2IP_NOT_FOUND)
                  res = IF2IP_AF_NOT_SUPPORTED;

                continue;
              }
#endif
              if(scopeid)
                snprintf(scope, sizeof(scope), "%%%u", scopeid);
            }
