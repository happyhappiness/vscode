  else
    hostname = conn->host.name;

  DEBUGASSERT(len > 32);

  /* put the number first so that the hostname gets cut off if too long */
  snprintf(buf, len, "%ld%s", conn->port, hostname);
}

/* Look up the bundle with all the connections to the same host this
