f(ai->ai_family == AF_INET)
      ss_size = sizeof(struct sockaddr_in);
#ifdef ENABLE_IPV6
    else if(ai->ai_family == AF_INET6)
      ss_size = sizeof(struct sockaddr_in6);
#endif
    else
      continue;