void *safe_calloc (size_t nmemb, size_t size)
{
  void *p;

  if (!nmemb || !size)
    return NULL;

  if (((size_t) -1) / nmemb <= size)
  {
    mutt_error _("Integer overflow -- can't allocate memory!");
    sleep (1);
    mutt_exit (1);
  }
  
  if (!(p = calloc (nmemb, size)))
  {
    mutt_error _("Out of memory!");
    sleep (1);
    mutt_exit (1);
  }
  return p;
}