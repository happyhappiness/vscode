int Curl_num_addresses(const Curl_addrinfo *addr)
{
  int i;
  for (i = 0; addr; addr = addr->ai_next, i++)
    ;  /* empty loop */
  return i;
}