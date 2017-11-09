int
_obstack_allocated_p (struct obstack *h, void *obj)
{
  register struct _obstack_chunk *lp;	/* below addr of any objects in this chunk */
  register struct _obstack_chunk *plp;	/* point to previous chunk if any */

  lp = (h)->chunk;
  /* We use >= rather than > since the object cannot be exactly at
     the beginning of the chunk but might be an empty object exactly
     at the end of an adjacent chunk.  */
  while (lp != NULL && ((void *) lp >= obj || (void *) (lp)->limit < obj))
    {
      plp = lp->prev;
      lp = plp;
    }
  return lp != NULL;
}