void
Curl_freeaddrinfo(Curl_addrinfo *cahead)
{
  Curl_addrinfo *vqualifier canext;
  Curl_addrinfo *ca;

  for(ca = cahead; ca != NULL; ca = canext) {
    free(ca->ai_addr);
    free(ca->ai_canonname);
    canext = ca->ai_next;

    free(ca);
  }
}