      break;

    }

  }

 

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = pf;

  hints.ai_socktype = SOCK_STREAM;

  hints.ai_flags = AI_CANONNAME;

  snprintf(sbuf, sizeof(sbuf), "%d", port);

  error = getaddrinfo(hostname, sbuf, &hints, &res);

  if (error) {

    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);    

    return NULL;

  }



  return res;

}

#endif /* USE_THREADING_GETADDRINFO */

#endif /* ipv6 */


