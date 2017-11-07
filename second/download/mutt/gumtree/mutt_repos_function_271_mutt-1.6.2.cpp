static void delete_hooks (int type)
{
  HOOK *h;
  HOOK *prev;

  while (h = Hooks, h && (type == 0 || type == h->type))
  {
    Hooks = h->next;
    delete_hook (h);
  }

  prev = h; /* Unused assignment to avoid compiler warnings */

  while (h)
  {
    if (type == h->type)
    {
      prev->next = h->next;
      delete_hook (h);
    }
    else
      prev = h;
    h = prev->next;
  }
}