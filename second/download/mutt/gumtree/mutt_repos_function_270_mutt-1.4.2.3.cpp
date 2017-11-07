int mutt_parse_pgp_hdr (char *p, int set_signas)
{
  int pgp = 0;
  char pgp_sign_as[LONG_STRING] = "\0", *q;
   
  SKIPWS (p);
  for (; *p; p++)
  {    
     
    switch (*p)
    {
      case 'e':
      case 'E':
        pgp |= PGPENCRYPT;
        break;

      case 's':    
      case 'S':
        pgp |= PGPSIGN;
        q = pgp_sign_as;
      
        if (*(p+1) == '<')
        {
          for (p += 2; 
	       *p && *p != '>' && q < pgp_sign_as + sizeof (pgp_sign_as) - 1;
               *q++ = *p++)
	    ;

          if (*p!='>')
          {
            mutt_error _("Illegal PGP header");
            return 0;
          }
        }
       
        *q = '\0';
        break;

      /* This used to be the micalg parameter.
       * 
       * It's no longer needed, so we just skip the parameter in order
       * to be able to recall old messages.
       */
      case 'm':
      case 'M':
        if(*(p+1) == '<')
        {
	  for (p += 2; *p && *p != '>'; p++)
	    ;
	  if(*p != '>')
	  {
	    mutt_error _("Illegal PGP header");
	    return 0;
	  }
	}

	break;
	  
      default:
        mutt_error _("Illegal PGP header");
        return 0;
    }
     
  }
 
  if (set_signas || *pgp_sign_as)
    mutt_str_replace (&PgpSignAs, pgp_sign_as);

  return pgp;
}