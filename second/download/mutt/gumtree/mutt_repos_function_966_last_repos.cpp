static void mix_free_remailer (REMAILER **r)
{
  FREE (&(*r)->shortname);
  FREE (&(*r)->addr);
  FREE (&(*r)->ver);
  
  FREE (r);		/* __FREE_CHECKED__ */
}