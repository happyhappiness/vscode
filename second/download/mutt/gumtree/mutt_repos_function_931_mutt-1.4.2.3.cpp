int mutt_needs_mailcap (BODY *m)
{
  switch (m->type)
  {
    case TYPETEXT:

      if (!ascii_strcasecmp ("plain", m->subtype) ||
	  !ascii_strcasecmp ("rfc822-headers", m->subtype) ||
	  !ascii_strcasecmp ("enriched", m->subtype))
	return 0;
      break;



#ifdef HAVE_PGP
    case TYPEAPPLICATION:
      if(mutt_is_application_pgp(m))
	return 0;
      break;
#endif /* HAVE_PGP */


    case TYPEMULTIPART:
    case TYPEMESSAGE:

      return 0;
  }

  return 1;
}