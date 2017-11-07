const char *mutt_fqdn(short may_hide_host)
{
  char *p = NULL, *q;
  
  if(Fqdn && Fqdn[0] != '@')
  {
    p = Fqdn;
    
    if(may_hide_host && option(OPTHIDDENHOST))
    {
      if((p = strchr(Fqdn, '.')))
	p++;

      /* sanity check: don't hide the host if
       * the fqdn is something like detebe.org.
       */
      
      if(!p || !(q = strchr(p, '.')))
	p = Fqdn;
    }
  }

  return p;
}