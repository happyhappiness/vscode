{
    osep = strchr(login, ';');

    /* Within the constraint of the login string */
    if(osep >= login + len)
      osep = NULL;
  }