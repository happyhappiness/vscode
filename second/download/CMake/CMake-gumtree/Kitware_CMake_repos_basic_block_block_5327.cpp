{
    smbc->user = slash + 1;
    smbc->domain = strdup(conn->user);
    if(!smbc->domain)
      return CURLE_OUT_OF_MEMORY;
    smbc->domain[slash - conn->user] = 0;
  }