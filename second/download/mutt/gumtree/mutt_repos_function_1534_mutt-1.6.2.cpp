int mutt_is_application_pgp (BODY *m)
{
  int t = 0;
  char *p;
  
  if (m->type == TYPEAPPLICATION)
  {
    if (!ascii_strcasecmp (m->subtype, "pgp") || !ascii_strcasecmp (m->subtype, "x-pgp-message"))
    {
      if ((p = mutt_get_parameter ("x-action", m->parameter))
	  && (!ascii_strcasecmp (p, "sign") || !ascii_strcasecmp (p, "signclear")))
	t |= PGPSIGN;

      if ((p = mutt_get_parameter ("format", m->parameter)) && 
	  !ascii_strcasecmp (p, "keys-only"))
	t |= PGPKEY;

      if(!t) t |= PGPENCRYPT;  /* not necessarily correct, but... */
    }

    if (!ascii_strcasecmp (m->subtype, "pgp-signed"))
      t |= PGPSIGN;

    if (!ascii_strcasecmp (m->subtype, "pgp-keys"))
      t |= PGPKEY;
  }
  else if (m->type == TYPETEXT && ascii_strcasecmp ("plain", m->subtype) == 0)
  {
    if (((p = mutt_get_parameter ("x-mutt-action", m->parameter))
	 || (p = mutt_get_parameter ("x-action", m->parameter)) 
	 || (p = mutt_get_parameter ("action", m->parameter)))
	 && !ascii_strncasecmp ("pgp-sign", p, 8))
      t |= PGPSIGN;
    else if (p && !ascii_strncasecmp ("pgp-encrypt", p, 11))
      t |= PGPENCRYPT;
    else if (p && !ascii_strncasecmp ("pgp-keys", p, 7))
      t |= PGPKEY;
  }
  if (t)
    t |= PGPINLINE;

  return t;
}