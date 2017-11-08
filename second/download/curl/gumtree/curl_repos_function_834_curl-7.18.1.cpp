void Curl_freeaddrinfo(Curl_addrinfo *ai)
{
  Curl_addrinfo *next;

  /* walk over the list and free all entries */
  while(ai) {
    next = ai->ai_next;
    if(ai->ai_canonname)
      free(ai->ai_canonname);
    free(ai);
    ai = next;
  }
}