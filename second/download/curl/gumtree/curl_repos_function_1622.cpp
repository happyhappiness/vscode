static void freednsentry(void *freethis)
{
  struct Curl_dns_entry *p = (struct Curl_dns_entry *) freethis;

  /* mark the entry as not in hostcache */
  p->timestamp = 0;
  if(p->inuse == 0) {
    Curl_freeaddrinfo(p->addr);
    free(p);
  }
}