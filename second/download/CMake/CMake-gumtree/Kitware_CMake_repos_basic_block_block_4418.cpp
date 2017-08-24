{
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

              addr =
                &((struct sockaddr_in6 *)(void *)iface->ifa_addr)->sin6_addr;
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
              /* Include the scope of this interface as part of the address */
              scopeid = ((struct sockaddr_in6 *)(void *)iface->ifa_addr)
                            ->sin6_scope_id;

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