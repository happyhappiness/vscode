int mutt_can_decode (BODY *a)
{
  char type[STRING];

  snprintf (type, sizeof (type), "%s/%s", TYPE (a), a->subtype);
  if (mutt_is_autoview (a, type))
    return (rfc1524_mailcap_lookup (a, type, NULL, M_AUTOVIEW));
  else if (a->type == TYPETEXT)
    return (1);
  else if (a->type == TYPEMESSAGE)
    return (1);
  else if (a->type == TYPEMULTIPART)
  {



#ifdef HAVE_PGP
    if (ascii_strcasecmp (a->subtype, "signed") == 0 ||
	ascii_strcasecmp (a->subtype, "encrypted") == 0)
      return (1);
    else
#endif



    {
      BODY *p;

      for (p = a->parts; p; p = p->next)
      {
	if (mutt_can_decode (p))
	  return (1);
      }
    }
  }



#ifdef HAVE_PGP
  else if (a->type == TYPEAPPLICATION)
  {
    if (mutt_is_application_pgp(a))
      return (1);
  }
#endif



  return (0);
}