struct loaded_l10nfile *
_nl_make_l10nflist (l10nfile_list, dirlist, dirlist_len, mask, language,
		    territory, codeset, normalized_codeset, modifier, special,
		    sponsor, revision, filename, do_allocate)
     struct loaded_l10nfile **l10nfile_list;
     const char *dirlist;
     size_t dirlist_len;
     int mask;
     const char *language;
     const char *territory;
     const char *codeset;
     const char *normalized_codeset;
     const char *modifier;
     const char *special;
     const char *sponsor;
     const char *revision;
     const char *filename;
     int do_allocate;
{
  char *abs_filename;
  struct loaded_l10nfile *last = NULL;
  struct loaded_l10nfile *retval;
  char *cp;
  size_t entries;
  int cnt;

  /* Allocate room for the full file name.  */
  abs_filename = (char *) malloc (dirlist_len
				  + strlen (language)
				  + ((mask & TERRITORY) != 0
				     ? strlen (territory) + 1 : 0)
				  + ((mask & XPG_CODESET) != 0
				     ? strlen (codeset) + 1 : 0)
				  + ((mask & XPG_NORM_CODESET) != 0
				     ? strlen (normalized_codeset) + 1 : 0)
				  + (((mask & XPG_MODIFIER) != 0
				      || (mask & CEN_AUDIENCE) != 0)
				     ? strlen (modifier) + 1 : 0)
				  + ((mask & CEN_SPECIAL) != 0
				     ? strlen (special) + 1 : 0)
				  + (((mask & CEN_SPONSOR) != 0
				      || (mask & CEN_REVISION) != 0)
				     ? (1 + ((mask & CEN_SPONSOR) != 0
					     ? strlen (sponsor) + 1 : 0)
					+ ((mask & CEN_REVISION) != 0
					   ? strlen (revision) + 1 : 0)) : 0)
				  + 1 + strlen (filename) + 1);

  if (abs_filename == NULL)
    return NULL;

  retval = NULL;
  last = NULL;

  /* Construct file name.  */
  memcpy (abs_filename, dirlist, dirlist_len);
  __argz_stringify (abs_filename, dirlist_len, PATH_SEPARATOR);
  cp = abs_filename + (dirlist_len - 1);
  *cp++ = '/';
  cp = stpcpy (cp, language);

  if ((mask & TERRITORY) != 0)
    {
      *cp++ = '_';
      cp = stpcpy (cp, territory);
    }
  if ((mask & XPG_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, codeset);
    }
  if ((mask & XPG_NORM_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, normalized_codeset);
    }
  if ((mask & (XPG_MODIFIER | CEN_AUDIENCE)) != 0)
    {
      /* This component can be part of both syntaces but has different
	 leading characters.  For CEN we use `+', else `@'.  */
      *cp++ = (mask & CEN_AUDIENCE) != 0 ? '+' : '@';
      cp = stpcpy (cp, modifier);
    }
  if ((mask & CEN_SPECIAL) != 0)
    {
      *cp++ = '+';
      cp = stpcpy (cp, special);
    }
  if ((mask & (CEN_SPONSOR | CEN_REVISION)) != 0)
    {
      *cp++ = ',';
      if ((mask & CEN_SPONSOR) != 0)
	cp = stpcpy (cp, sponsor);
      if ((mask & CEN_REVISION) != 0)
	{
	  *cp++ = '_';
	  cp = stpcpy (cp, revision);
	}
    }

  *cp++ = '/';
  stpcpy (cp, filename);

  /* Look in list of already loaded domains whether it is already
     available.  */
  last = NULL;
  for (retval = *l10nfile_list; retval != NULL; retval = retval->next)
    if (retval->filename != NULL)
      {
	int compare = strcmp (retval->filename, abs_filename);
	if (compare == 0)
	  /* We found it!  */
	  break;
	if (compare < 0)
	  {
	    /* It's not in the list.  */
	    retval = NULL;
	    break;
	  }

	last = retval;
      }

  if (retval != NULL || do_allocate == 0)
    {
      free (abs_filename);
      return retval;
    }

  retval = (struct loaded_l10nfile *)
    malloc (sizeof (*retval) + (__argz_count (dirlist, dirlist_len)
				* (1 << pop (mask))
				* sizeof (struct loaded_l10nfile *)));
  if (retval == NULL)
    return NULL;

  retval->filename = abs_filename;
  retval->decided = (__argz_count (dirlist, dirlist_len) != 1
		     || ((mask & XPG_CODESET) != 0
			 && (mask & XPG_NORM_CODESET) != 0));
  retval->data = NULL;

  if (last == NULL)
    {
      retval->next = *l10nfile_list;
      *l10nfile_list = retval;
    }
  else
    {
      retval->next = last->next;
      last->next = retval;
    }

  entries = 0;
  /* If the DIRLIST is a real list the RETVAL entry corresponds not to
     a real file.  So we have to use the DIRLIST separation mechanism
     of the inner loop.  */
  cnt = __argz_count (dirlist, dirlist_len) == 1 ? mask - 1 : mask;
  for (; cnt >= 0; --cnt)
    if ((cnt & ~mask) == 0
	&& ((cnt & CEN_SPECIFIC) == 0 || (cnt & XPG_SPECIFIC) == 0)
	&& ((cnt & XPG_CODESET) == 0 || (cnt & XPG_NORM_CODESET) == 0))
      {
	/* Iterate over all elements of the DIRLIST.  */
	char *dir = NULL;

	while ((dir = __argz_next ((char *) dirlist, dirlist_len, dir))
	       != NULL)
	  retval->successor[entries++]
	    = _nl_make_l10nflist (l10nfile_list, dir, strlen (dir) + 1, cnt,
				  language, territory, codeset,
				  normalized_codeset, modifier, special,
				  sponsor, revision, filename, 1);
      }
  retval->successor[entries] = NULL;

  return retval;
}