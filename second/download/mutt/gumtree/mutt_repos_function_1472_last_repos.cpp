void mutt_free_regexp (REGEXP **pp)
{
  FREE (&(*pp)->pattern);
  regfree ((*pp)->rx);
  FREE (&(*pp)->rx);
  FREE (pp);		/* __FREE_CHECKED__ */
}