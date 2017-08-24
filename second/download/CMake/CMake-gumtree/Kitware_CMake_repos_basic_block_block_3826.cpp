{
    free(ca->ai_addr);
    free(ca->ai_canonname);
    canext = ca->ai_next;

    free(ca);
  }