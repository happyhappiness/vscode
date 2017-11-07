int mutt_is_text_type (int t, char *s)
{
  if (t == TYPETEXT)
    return 1;

  if (t == TYPEMESSAGE)
  {
    if (!ascii_strcasecmp ("delivery-status", s))
      return 1;
  }



#ifdef HAVE_PGP
  if (t == TYPEAPPLICATION)
  {
    if (!ascii_strcasecmp ("pgp-keys", s))
      return 1;
  }
#endif /* HAVE_PGP */



  return 0;
}