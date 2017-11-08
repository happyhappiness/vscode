static int
#ifdef _LIBC
internal_function
#endif
internal_fnmatch (const char *pattern, const char *string,
		  int no_leading_period, int flags)
{
  register const char *p = pattern, *n = string;
  register unsigned char c;

/* Note that this evaluates C many times.  */
# ifdef _LIBC
#  define FOLD(c) ((flags & FNM_CASEFOLD) ? tolower (c) : (c))
# else
#  define FOLD(c) ((flags & FNM_CASEFOLD) && ISUPPER (c) ? tolower (c) : (c))
# endif

  while ((c = *p++) != '\0')
    {
      c = FOLD (c);

      switch (c)
	{
	case '?':
	  if (*n == '\0')
	    return FNM_NOMATCH;
	  else if (*n == '/' && (flags & FNM_FILE_NAME))
	    return FNM_NOMATCH;
	  else if (*n == '.' && no_leading_period
		   && (n == string
		       || (n[-1] == '/' && (flags & FNM_FILE_NAME))))
	    return FNM_NOMATCH;
	  break;

	case '\\':
	  if (!(flags & FNM_NOESCAPE))
	    {
	      c = *p++;
	      if (c == '\0')
		/* Trailing \ loses.  */
		return FNM_NOMATCH;
	      c = FOLD (c);
	    }
	  if (FOLD ((unsigned char) *n) != c)
	    return FNM_NOMATCH;
	  break;

	case '*':
	  if (*n == '.' && no_leading_period
	      && (n == string
		  || (n[-1] == '/' && (flags & FNM_FILE_NAME))))
	    return FNM_NOMATCH;

	  for (c = *p++; c == '?' || c == '*'; c = *p++)
	    {
	      if (*n == '/' && (flags & FNM_FILE_NAME))
		/* A slash does not match a wildcard under FNM_FILE_NAME.  */
		return FNM_NOMATCH;
	      else if (c == '?')
		{
		  /* A ? needs to match one character.  */
		  if (*n == '\0')
		    /* There isn't another character; no match.  */
		    return FNM_NOMATCH;
		  else
		    /* One character of the string is consumed in matching
		       this ? wildcard, so *??? won't match if there are
		       less than three characters.  */
		    ++n;
		}
	    }

	  if (c == '\0')
	    /* The wildcard(s) is/are the last element of the pattern.
	       If the name is a file name and contains another slash
	       this does mean it cannot match.  */
	    return ((flags & FNM_FILE_NAME) && strchr (n, '/') != NULL
		    ? FNM_NOMATCH : 0);
	  else
	    {
	      const char *endp;

#if 0
	      endp = __strchrnul (n, (flags & FNM_FILE_NAME) ? '/' : '\0');
#else
/* replace call to internal glibc function with equivalent */
	      if (!(flags & FNM_FILE_NAME) || ((endp = strchr(n, '/')) == NULL))
		endp = n + strlen(n);
#endif

	      if (c == '[')
		{
		  int flags2 = ((flags & FNM_FILE_NAME)
				? flags : (flags & ~FNM_PERIOD));

		  for (--p; n < endp; ++n)
		    if (internal_fnmatch (p, n,
					  (no_leading_period
					   && (n == string
					       || (n[-1] == '/'
						   && (flags
						       & FNM_FILE_NAME)))),
					  flags2)
			== 0)
		      return 0;
		}
	      else if (c == '/' && (flags & FNM_FILE_NAME))
		{
		  while (*n != '\0' && *n != '/')
		    ++n;
		  if (*n == '/'
		      && (internal_fnmatch (p, n + 1, flags & FNM_PERIOD,
					    flags) == 0))
		    return 0;
		}
	      else
		{
		  int flags2 = ((flags & FNM_FILE_NAME)
				? flags : (flags & ~FNM_PERIOD));

		  if (c == '\\' && !(flags & FNM_NOESCAPE))
		    c = *p;
		  c = FOLD (c);
		  for (--p; n < endp; ++n)
		    if (FOLD ((unsigned char) *n) == c
			&& (internal_fnmatch (p, n,
					      (no_leading_period
					       && (n == string
						   || (n[-1] == '/'
						       && (flags
							   & FNM_FILE_NAME)))),
					      flags2) == 0))
		      return 0;
		}
	    }

	  /* If we come here no match is possible with the wildcard.  */
	  return FNM_NOMATCH;

	case '[':
	  {
	    /* Nonzero if the sense of the character class is inverted.  */
	    static int posixly_correct;
	    register int not;
	    char cold;

	    if (posixly_correct == 0)
	      posixly_correct = getenv ("POSIXLY_CORRECT") != NULL ? 1 : -1;

	    if (*n == '\0')
	      return FNM_NOMATCH;

	    if (*n == '.' && no_leading_period && (n == string
						   || (n[-1] == '/'
						       && (flags
							   & FNM_FILE_NAME))))
	      return FNM_NOMATCH;

	    if (*n == '/' && (flags & FNM_FILE_NAME))
	      /* `/' cannot be matched.  */
	      return FNM_NOMATCH;

	    not = (*p == '!' || (posixly_correct < 0 && *p == '^'));
	    if (not)
	      ++p;

	    c = *p++;
	    for (;;)
	      {
		unsigned char fn = FOLD ((unsigned char) *n);

		if (!(flags & FNM_NOESCAPE) && c == '\\')
		  {
		    if (*p == '\0')
		      return FNM_NOMATCH;
		    c = FOLD ((unsigned char) *p);
		    ++p;

		    if (c == fn)
		      goto matched;
		  }
		else if (c == '[' && *p == ':')
		  {
		    /* Leave room for the null.  */
		    char str[CHAR_CLASS_MAX_LENGTH + 1];
		    size_t c1 = 0;
# if defined _LIBC || (defined HAVE_WCTYPE_H && defined HAVE_WCHAR_H)
		    wctype_t wt;
# endif
		    const char *startp = p;

		    for (;;)
		      {
			if (c1 == CHAR_CLASS_MAX_LENGTH)
			  /* The name is too long and therefore the pattern
			     is ill-formed.  */
			  return FNM_NOMATCH;

			c = *++p;
			if (c == ':' && p[1] == ']')
			  {
			    p += 2;
			    break;
			  }
			if (c < 'a' || c >= 'z')
			  {
			    /* This cannot possibly be a character class name.
			       Match it as a normal range.  */
			    p = startp;
			    c = '[';
			    goto normal_bracket;
			  }
			str[c1++] = c;
		      }
		    str[c1] = '\0';

# if defined _LIBC || (defined HAVE_WCTYPE_H && defined HAVE_WCHAR_H)
		    wt = IS_CHAR_CLASS (str);
		    if (wt == 0)
		      /* Invalid character class name.  */
		      return FNM_NOMATCH;

		    if (__iswctype (__btowc ((unsigned char) *n), wt))
		      goto matched;
# else
		    if ((STREQ (str, "alnum") && ISALNUM ((unsigned char) *n))
			|| (STREQ (str, "alpha") && ISALPHA ((unsigned char) *n))
			|| (STREQ (str, "blank") && ISBLANK ((unsigned char) *n))
			|| (STREQ (str, "cntrl") && ISCNTRL ((unsigned char) *n))
			|| (STREQ (str, "digit") && ISDIGIT ((unsigned char) *n))
			|| (STREQ (str, "graph") && ISGRAPH ((unsigned char) *n))
			|| (STREQ (str, "lower") && ISLOWER ((unsigned char) *n))
			|| (STREQ (str, "print") && ISPRINT ((unsigned char) *n))
			|| (STREQ (str, "punct") && ISPUNCT ((unsigned char) *n))
			|| (STREQ (str, "space") && ISSPACE ((unsigned char) *n))
			|| (STREQ (str, "upper") && ISUPPER ((unsigned char) *n))
			|| (STREQ (str, "xdigit") && ISXDIGIT ((unsigned char) *n)))
		      goto matched;
# endif
		  }
		else if (c == '\0')
		  /* [ (unterminated) loses.  */
		  return FNM_NOMATCH;
		else
		  {
		  normal_bracket:
		    if (FOLD (c) == fn)
		      goto matched;

		    cold = c;
		    c = *p++;

		    if (c == '-' && *p != ']')
		      {
			/* It is a range.  */
			unsigned char cend = *p++;
			if (!(flags & FNM_NOESCAPE) && cend == '\\')
			  cend = *p++;
			if (cend == '\0')
			  return FNM_NOMATCH;

			if (cold <= fn && fn <= FOLD (cend))
			  goto matched;

			c = *p++;
		      }
		  }

		if (c == ']')
		  break;
	      }

	    if (!not)
	      return FNM_NOMATCH;
	    break;

	  matched:
	    /* Skip the rest of the [...] that already matched.  */
	    while (c != ']')
	      {
		if (c == '\0')
		  /* [... (unterminated) loses.  */
		  return FNM_NOMATCH;

		c = *p++;
		if (!(flags & FNM_NOESCAPE) && c == '\\')
		  {
		    if (*p == '\0')
		      return FNM_NOMATCH;
		    /* XXX 1003.2d11 is unclear if this is right.  */
		    ++p;
		  }
		else if (c == '[' && *p == ':')
		  {
		    do
		      if (*++p == '\0')
			return FNM_NOMATCH;
		    while (*p != ':' || p[1] == ']');
		    p += 2;
		    c = *p;
		  }
	      }
	    if (not)
	      return FNM_NOMATCH;
	  }
	  break;

	default:
	  if (c != FOLD ((unsigned char) *n))
	    return FNM_NOMATCH;
	}

      ++n;
    }

  if (*n == '\0')
    return 0;

  if ((flags & FNM_LEADING_DIR) && *n == '/')
    /* The FNM_LEADING_DIR flag says that "foo*" matches "foobar/frobozz".  */
    return 0;

  return FNM_NOMATCH;

# undef FOLD
}