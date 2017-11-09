static void destroy_async_data(struct Curl_async *async)
{
  free(async->hostname);

  if(async->os_specific) {
    struct ResolverResults *res = (struct ResolverResults *)async->os_specific;
    if(res) {
      if(res->temp_ai) {
        Curl_freeaddrinfo(res->temp_ai);
        res->temp_ai = NULL;
      }
      free(res);
    }
    async->os_specific = NULL;
  }

  async->hostname = NULL;
}