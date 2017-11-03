void pgp_free_sig (pgp_sig_t **sigp)
{
  pgp_sig_t *sp, *q;
  
  if (!sigp || !*sigp)
    return;
  
  for (sp = *sigp; sp; sp = q)
  {
    q = sp->next;
    FREE (&sp);
  }
  
  *sigp = NULL;
}