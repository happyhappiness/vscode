static void
free_cookiemess(struct Cookie *co)
{
  if(co->domain)
    free(co->domain);
  if(co->path)
    free(co->path);
  if(co->name)
    free(co->name);
  if(co->value)
    free(co->value);

  free(co);
}