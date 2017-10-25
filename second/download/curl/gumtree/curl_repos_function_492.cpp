static void freednsentry(void *freethis)
{
  struct Curl_dns_entry *p = (struct Curl_dns_entry *) freethis;

  Curl_freeaddrinfo(p->addr);

  free(p);
}