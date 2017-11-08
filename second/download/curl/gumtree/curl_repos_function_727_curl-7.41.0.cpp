static metalink_resource *new_metalink_resource(const char *url)
{
  metalink_resource *res;
  res = malloc(sizeof(metalink_resource));
  res->next = NULL;
  res->url = strdup(url);
  return res;
}