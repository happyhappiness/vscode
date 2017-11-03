void mutt_check_simple (char *s, size_t len, const char *simple)
{
  char tmp[LONG_STRING];
  int do_simple = 1;
  char *p;

  for (p = s; p && *p; p++)
  {
    if (*p == '\\' && *(p + 1))
      p++;
    else if (*p == '~' || *p == '=' || *p == '%')
    {
      do_simple = 0;
      break;
    }
  }

  /* XXX - is ascii_strcasecmp() right here, or should we use locale's
   * equivalences?
   */

  if (do_simple) /* yup, so spoof a real request */
  {
    /* convert old tokens into the new format */
    if (ascii_strcasecmp ("all", s) == 0 ||
	!mutt_strcmp ("^", s) || !mutt_strcmp (".", s)) /* ~A is more efficient */
      strfcpy (s, "~A", len);
    else if (ascii_strcasecmp ("del", s) == 0)
      strfcpy (s, "~D", len);
    else if (ascii_strcasecmp ("flag", s) == 0)
      strfcpy (s, "~F", len);
    else if (ascii_strcasecmp ("new", s) == 0)
      strfcpy (s, "~N", len);
    else if (ascii_strcasecmp ("old", s) == 0)
      strfcpy (s, "~O", len);
    else if (ascii_strcasecmp ("repl", s) == 0)
      strfcpy (s, "~Q", len);
    else if (ascii_strcasecmp ("read", s) == 0)
      strfcpy (s, "~R", len);
    else if (ascii_strcasecmp ("tag", s) == 0)
      strfcpy (s, "~T", len);
    else if (ascii_strcasecmp ("unread", s) == 0)
      strfcpy (s, "~U", len);
    else
    {
      quote_simple (tmp, sizeof(tmp), s);
      mutt_expand_fmt (s, len, simple, tmp);
    }
  }
}