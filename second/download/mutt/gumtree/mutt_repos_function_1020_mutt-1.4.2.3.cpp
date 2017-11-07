static void maildir_parse_flags(HEADER *h, const char *path)
{
  char *p;

  h->flagged = 0;
  h->read = 0;
  h->replied = 0;
  
  if ((p = strrchr (path, ':')) != NULL && mutt_strncmp (p + 1, "2,", 2) == 0)
  {
    p += 3;
    while (*p)
    {
      switch (*p)
      {
	case 'F':
	
	h->flagged = 1;
	break;
	
	case 'S': /* seen */
	
	h->read = 1;
	break;
	
	case 'R': /* replied */
	
	h->replied = 1;
	break;

	case 'T': /* trashed */
	h->trash   = 1;
	h->deleted = 1;
	break;
      }
      p++;
    }
  }
}