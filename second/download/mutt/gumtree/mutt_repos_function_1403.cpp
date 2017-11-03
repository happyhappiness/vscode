void mutt_buffer_free (BUFFER **p)
{
  if (!p || !*p) 
    return;

   FREE(&(*p)->data);
   /* dptr is just an offset to data and shouldn't be freed */
   FREE(p);		/* __FREE_CHECKED__ */
}