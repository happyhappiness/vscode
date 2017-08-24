{
    req->addrinfow = (struct addrinfoW*)alloc_ptr;
    req->addrinfow->ai_family = hints->ai_family;
    req->addrinfow->ai_socktype = hints->ai_socktype;
    req->addrinfow->ai_protocol = hints->ai_protocol;
    req->addrinfow->ai_flags = hints->ai_flags;
    req->addrinfow->ai_addrlen = 0;
    req->addrinfow->ai_canonname = NULL;
    req->addrinfow->ai_addr = NULL;
    req->addrinfow->ai_next = NULL;
  }