local int inflate_trees_free(t, z)
inflate_huft *t;        /* table to free */
z_stream *z;            /* for zfree function */
/* Free the malloc'ed tables built by huft_build(), which makes a linked
   list of the tables it made, with the links in a dummy first entry of
   each table. */
{
  register inflate_huft *p, *q;

  /* Go through linked list, freeing from the malloced (t[-1]) address. */
  p = t;
  while (p != Z_NULL)
  {
    q = (--p)->next;
    ZFREE(z, p, p->word.Nalloc * sizeof(inflate_huft));
    p = q;
  } 
  return Z_OK;
}