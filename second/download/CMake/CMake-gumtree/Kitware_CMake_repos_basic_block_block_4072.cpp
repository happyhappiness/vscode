{
    infof(data, "Hostname %s was found in DNS cache\n", hostname);
    dns->inuse++; /* we use it! */
    rc = CURLRESOLV_RESOLVED;
  }