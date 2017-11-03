char *_mutt_expand_path (char *s, size_t slen, int rx)
{
  char p[_POSIX_PATH_MAX] = "";
  char q[_POSIX_PATH_MAX] = "";
  char tmp[_POSIX_PATH_MAX];
  char *t;

  char *tail = ""; 

  int recurse = 0;
  
  do 
  {
    recurse = 0;

    switch (*s)
    {
      case '~':
      {
	if (*(s + 1) == '/' || *(s + 1) == 0)
	{
	  strfcpy (p, NONULL(Homedir), sizeof (p));
	  tail = s + 1;
	}
	else
	{
	  struct passwd *pw;
	  if ((t = strchr (s + 1, '/'))) 
	    *t = 0;

	  if ((pw = getpwnam (s + 1)))
	  {
	    strfcpy (p, pw->pw_dir, sizeof (p));
	    if (t)
	    {
	      *t = '/';
	      tail = t;
	    }
	    else
	      tail = "";
	  }
	  else
	  {
	    /* user not found! */
	    if (t)
	      *t = '/';
	    *p = '\0';
	    tail = s;
	  }
	}
      }
      break;
      
      case '=':
      case '+':    
      {
#ifdef USE_IMAP
	/* if folder = {host} or imap[s]://host/: don't append slash */
	if (mx_is_imap (NONULL (Maildir)) &&
	    (Maildir[strlen (Maildir) - 1] == '}' ||
	     Maildir[strlen (Maildir) - 1] == '/'))
	  strfcpy (p, NONULL (Maildir), sizeof (p));
	else
#endif
	if (Maildir && *Maildir && Maildir[strlen (Maildir) - 1] == '/')
	  strfcpy (p, NONULL (Maildir), sizeof (p));
	else
	  snprintf (p, sizeof (p), "%s/", NONULL (Maildir));
	
	tail = s + 1;
      }
      break;
      
      /* elm compatibility, @ expands alias to user name */
    
      case '@':
      {
	HEADER *h;
	ADDRESS *alias;
	
	if ((alias = mutt_lookup_alias (s + 1)))
	{
	  h = mutt_new_header();
	  h->env = mutt_new_envelope();
	  h->env->from = h->env->to = alias;
	  mutt_default_save (p, sizeof (p), h);
	  h->env->from = h->env->to = NULL;
	  mutt_free_header (&h);
	  /* Avoid infinite recursion if the resulting folder starts with '@' */
	  if (*p != '@')
	    recurse = 1;
	  
	  tail = "";
	}
      }
      break;
      
      case '>':
      {
	strfcpy (p, NONULL(Inbox), sizeof (p));
	tail = s + 1;
      }
      break;
      
      case '<':
      {
	strfcpy (p, NONULL(Outbox), sizeof (p));
	tail = s + 1;
      }
      break;
      
      case '!':
      {
	if (*(s+1) == '!')
	{
	  strfcpy (p, NONULL(LastFolder), sizeof (p));
	  tail = s + 2;
	}
	else 
	{
	  strfcpy (p, NONULL(Spoolfile), sizeof (p));
	  tail = s + 1;
	}
      }
      break;
      
      case '-':
      {
	strfcpy (p, NONULL(LastFolder), sizeof (p));
	tail = s + 1;
      }
      break;
      
      case '^':        
      {
	strfcpy (p, NONULL(CurrentFolder), sizeof (p));
	tail = s + 1;
      }
      break;

      default:
      {
	*p = '\0';
	tail = s;
      }
    }

    if (rx && *p && !recurse)
    {
      mutt_rx_sanitize_string (q, sizeof (q), p);
      snprintf (tmp, sizeof (tmp), "%s%s", q, tail);
    }
    else
      snprintf (tmp, sizeof (tmp), "%s%s", p, tail);
    
    strfcpy (s, tmp, slen);
  }
  while (recurse);

#ifdef USE_IMAP
  /* Rewrite IMAP path in canonical form - aids in string comparisons of
   * folders. May possibly fail, in which case s should be the same. */
  if (mx_is_imap (s))
    imap_expand_path (s, slen);
#endif

  return (s);
}