char *mutt_apply_replace (char *dbuf, size_t dlen, char *sbuf, REPLACE_LIST *rlist)
{
  REPLACE_LIST *l;
  static regmatch_t *pmatch = NULL;
  static int nmatch = 0;
  static char twinbuf[2][LONG_STRING];
  int switcher = 0;
  char *p;
  int i, n;
  size_t cpysize, tlen;
  char *src, *dst;

  if (dbuf && dlen)
    dbuf[0] = '\0';

  if (sbuf == NULL || *sbuf == '\0' || (dbuf && !dlen))
    return dbuf;

  twinbuf[0][0] = '\0';
  twinbuf[1][0] = '\0';
  src = twinbuf[switcher];
  dst = src;

  strfcpy(src, sbuf, LONG_STRING);

  for (l = rlist; l; l = l->next)
  {
    /* If this pattern needs more matches, expand pmatch. */
    if (l->nmatch > nmatch)
    {
      safe_realloc (&pmatch, l->nmatch * sizeof(regmatch_t));
      nmatch = l->nmatch;
    }

    if (regexec (l->rx->rx, src, l->nmatch, pmatch, 0) == 0)
    {
      tlen = 0;
      switcher ^= 1;
      dst = twinbuf[switcher];

      dprint (5, (debugfile, "mutt_apply_replace: %s matches %s\n", src, l->rx->pattern));

      /* Copy into other twinbuf with substitutions */
      if (l->template)
      {
        for (p = l->template; *p && (tlen < LONG_STRING - 1); )
        {
	  if (*p == '%')
	  {
	    p++;
	    if (*p == 'L')
	    {
	      p++;
              cpysize = MIN (pmatch[0].rm_so, LONG_STRING - tlen - 1);
	      strncpy(&dst[tlen], src, cpysize);
	      tlen += cpysize;
	    }
	    else if (*p == 'R')
	    {
	      p++;
              cpysize = MIN (strlen (src) - pmatch[0].rm_eo, LONG_STRING - tlen - 1);
	      strncpy(&dst[tlen], &src[pmatch[0].rm_eo], cpysize);
	      tlen += cpysize;
	    }
	    else
	    {
	      n = strtoul(p, &p, 10);               /* get subst number */
	      while (isdigit((unsigned char)*p))    /* skip subst token */
                ++p;
	      for (i = pmatch[n].rm_so; (i < pmatch[n].rm_eo) && (tlen < LONG_STRING-1); i++)
	        dst[tlen++] = src[i];
	    }
	  }
	  else
	    dst[tlen++] = *p++;
        }
      }
      dst[tlen] = '\0';
      dprint (5, (debugfile, "mutt_apply_replace: subst %s\n", dst));
    }
    src = dst;
  }

  if (dbuf)
    strfcpy(dbuf, dst, dlen);
  else
    dbuf = safe_strdup(dst);
  return dbuf;
}