int mutt_match_spam_list (const char *s, SPAM_LIST *l, char *text, int textsize)
{
  static regmatch_t *pmatch = NULL;
  static int nmatch = 0;
  int tlen = 0;
  char *p;

  if (!s) return 0;

  for (; l; l = l->next)
  {
    /* If this pattern needs more matches, expand pmatch. */
    if (l->nmatch > nmatch)
    {
      safe_realloc (&pmatch, l->nmatch * sizeof(regmatch_t));
      nmatch = l->nmatch;
    }

    /* Does this pattern match? */
    if (regexec (l->rx->rx, s, (size_t) l->nmatch, (regmatch_t *) pmatch, (int) 0) == 0)
    {
      dprint (5, (debugfile, "mutt_match_spam_list: %s matches %s\n", s, l->rx->pattern));
      dprint (5, (debugfile, "mutt_match_spam_list: %d subs\n", (int)l->rx->rx->re_nsub));

      /* Copy template into text, with substitutions. */
      for (p = l->template; *p && tlen < textsize - 1;)
      {
	/* backreference to pattern match substring, eg. %1, %2, etc) */
	if (*p == '%')
	{
	  char *e; /* used as pointer to end of integer backreference in strtol() call */
	  int n;

	  ++p; /* skip over % char */
	  n = strtol(p, &e, 10);
	  /* Ensure that the integer conversion succeeded (e!=p) and bounds check.  The upper bound check
	   * should not strictly be necessary since add_to_spam_list() finds the largest value, and
	   * the static array above is always large enough based on that value. */
	  if (e != p && n >= 0 && n <= l->nmatch && pmatch[n].rm_so != -1) {
	    /* copy as much of the substring match as will fit in the output buffer, saving space for
	     * the terminating nul char */
	    int idx;
	    for (idx = pmatch[n].rm_so; (idx < pmatch[n].rm_eo) && (tlen < textsize - 1); ++idx)
	      text[tlen++] = s[idx];
	  }
	  p = e; /* skip over the parsed integer */
	}
	else
	{
	  text[tlen++] = *p++;
	}
      }
      /* tlen should always be less than textsize except when textsize<=0
       * because the bounds checks in the above code leave room for the
       * terminal nul char.   This should avoid returning an unterminated
       * string to the caller.  When textsize<=0 we make no assumption about
       * the validity of the text pointer. */
      if (tlen < textsize) {
	text[tlen] = '\0';
	dprint (5, (debugfile, "mutt_match_spam_list: \"%s\"\n", text));
      }
      return 1;
    }
  }

  return 0;
}