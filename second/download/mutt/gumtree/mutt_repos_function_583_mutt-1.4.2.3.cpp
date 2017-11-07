static void mix_free_remailer (REMAILER **r)
{
  safe_free ((void **) &(*r)->shortname);
  safe_free ((void **) &(*r)->addr);
  safe_free ((void **) &(*r)->ver);
  
  safe_free ((void **) r);
}