static void maildir_parse_flags (HEADER * h, const char *path)
{
  char *p, *q = NULL;

  h->flagged = 0;
  h->read = 0;
  h->replied = 0;

  if ((p = strrchr (path, ':')) != NULL && mutt_strncmp (p + 1, "2,", 2) == 0)
  {
    p += 3;
    
    mutt_str_replace (&h->maildir_flags, p);
    q = h->maildir_flags;

    while (*p)
    {
      switch (*p)
      {
      case 'F':

	h->flagged = 1;
	break;

      case 'S':		/* seen */

	h->read = 1;
	break;

      case 'R':		/* replied */

	h->replied = 1;
	break;

      case 'T':		/* trashed */
	if (!h->flagged || !option(OPTFLAGSAFE))
	{
	  h->trash = 1;
	  h->deleted = 1;
	}
	break;
      
      default:
	*q++ = *p;
	break;
      }
      p++;
    }
  }
  
  if (q == h->maildir_flags)
    FREE (&h->maildir_flags);
  else if (q)
    *q = '\0';
}