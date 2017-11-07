static void rfc2231_free_parameter (struct rfc2231_parameter **p)
{
  if (*p)
  {
    safe_free ((void **) &(*p)->attribute);
    safe_free ((void **) &(*p)->value);
    safe_free ((void **) p);
  }
}