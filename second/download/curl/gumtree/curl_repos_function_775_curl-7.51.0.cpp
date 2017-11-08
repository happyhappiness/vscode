static metalink_resource *new_metalink_resource(const char *url)
{
  metalink_resource *res;
  res = malloc(sizeof(metalink_resource));
  if(res) {
    res->next = NULL;
    res->url = strdup(url);
    if(!res->url) {
      free(res);
      return NULL;
    }
  }
  return res;
}