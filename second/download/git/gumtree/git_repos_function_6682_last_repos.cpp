int
_obstack_memory_used (struct obstack *h)
{
  register struct _obstack_chunk* lp;
  register int nbytes = 0;

  for (lp = h->chunk; lp != NULL; lp = lp->prev)
    {
      nbytes += lp->limit - (char *) lp;
    }
  return nbytes;
}