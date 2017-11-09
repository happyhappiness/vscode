static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;
  size_t tocopy = size * nmemb;

  /* Wait one second before return POST data          *
   * so libcurl will wait before sending request body */
  wait_ms(1000);

  if(tocopy < 1 || !pooh->sizeleft)
    return 0;

  if(pooh->sizeleft < tocopy)
    tocopy = pooh->sizeleft;

  memcpy(ptr, pooh->readptr, tocopy);/* copy requested data */
  pooh->readptr += tocopy;           /* advance pointer */
  pooh->sizeleft -= tocopy;          /* less data left */
  return tocopy;
}