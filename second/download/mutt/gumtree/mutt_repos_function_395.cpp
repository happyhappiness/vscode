int mutt_parse_crypt_hdr (const char *p, int set_empty_signas, int crypt_app)
{
  char smime_cryptalg[LONG_STRING] = "\0";
  char sign_as[LONG_STRING] = "\0", *q;
  int flags = 0;

  if (!WithCrypto)
    return 0;

  p = skip_email_wsp(p);
  for (; *p; p++)
  {

    switch (*p)
    {
      case 'e':
      case 'E':
        flags |= ENCRYPT;
        break;

      case 'o':
      case 'O':
        flags |= OPPENCRYPT;
        break;

      case 's':
      case 'S':
        flags |= SIGN;
        q = sign_as;

        if (*(p+1) == '<')
        {
          for (p += 2;
	       *p && *p != '>' && q < sign_as + sizeof (sign_as) - 1;
               *q++ = *p++)
	    ;

          if (*p!='>')
          {
            mutt_error _("Illegal crypto header");
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
	    mutt_error _("Illegal crypto header");
	    return 0;
	  }
	}

	break;


      case 'c':
      case 'C':
   	q = smime_cryptalg;

        if(*(p+1) == '<')
	{
	  for(p += 2; *p && *p != '>' && q < smime_cryptalg + sizeof(smime_cryptalg) - 1;
	      *q++ = *p++)
	    ;

	  if(*p != '>')
	  {
	    mutt_error _("Illegal S/MIME header");
	    return 0;
	  }
	}

	*q = '\0';
	break;

      case 'i':
      case 'I':
	flags |= INLINE;
	break;

      default:
        mutt_error _("Illegal crypto header");
        return 0;
    }

  }

  /* the cryptalg field must not be empty */
  if ((WithCrypto & APPLICATION_SMIME) && *smime_cryptalg)
    mutt_str_replace (&SmimeCryptAlg, smime_cryptalg);

  /* Set {Smime,Pgp}SignAs, if desired. */

  if ((WithCrypto & APPLICATION_PGP) && (crypt_app == APPLICATION_PGP)
      && (flags & SIGN)
      && (set_empty_signas || *sign_as))
    mutt_str_replace (&PgpSignAs, sign_as);

  if ((WithCrypto & APPLICATION_SMIME) && (crypt_app == APPLICATION_SMIME)
      && (flags & SIGN)
      && (set_empty_signas || *sign_as))
    mutt_str_replace (&SmimeDefaultKey, sign_as);

  return flags;
}