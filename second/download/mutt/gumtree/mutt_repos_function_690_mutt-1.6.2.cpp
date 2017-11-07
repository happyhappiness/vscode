static void show_fingerprint (gpgme_key_t key, STATE *state)
{
  const char *s;
  int i, is_pgp;
  char *buf, *p;
  const char *prefix = _("Fingerprint: ");

  if (!key)
    return;
  s = key->subkeys ? key->subkeys->fpr : NULL;
  if (!s)
    return;
  is_pgp = (key->protocol == GPGME_PROTOCOL_OpenPGP);

  buf = safe_malloc ( strlen (prefix) + strlen(s) * 4 + 2 );
  strcpy (buf, prefix); /* __STRCPY_CHECKED__ */
  p = buf + strlen (buf);
  if (is_pgp && strlen (s) == 40)
    {  /* PGP v4 style formatted. */
      for (i=0; *s && s[1] && s[2] && s[3] && s[4]; s += 4, i++)
        {
          *p++ = s[0];
          *p++ = s[1];
          *p++ = s[2];
          *p++ = s[3];
          *p++ = ' ';
          if (i == 4)
            *p++ = ' ';
        }
    }
  else
    {
      for (i=0; *s && s[1] && s[2]; s += 2, i++)
        {
          *p++ = s[0];
          *p++ = s[1];
          *p++ = is_pgp? ' ':':';
          if (is_pgp && i == 7)
            *p++ = ' ';
        }
    }

  /* just in case print remaining odd digits */
  for (; *s; s++)
    *p++ = *s;
  *p++ = '\n';
  *p = 0;
  state_attach_puts (buf, state);
  FREE (&buf);
}