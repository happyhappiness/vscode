static const char * parse_date_range (const char* pc, struct tm *min,
    struct tm *max, int haveMin, struct tm *baseMin, BUFFER *err)
{
  int flag = MUTT_PDR_NONE;	
  while (*pc && ((flag & MUTT_PDR_DONE) == 0))
  {
    const char *pt;
    char ch = *pc++;
    SKIPWS (pc);
    switch (ch)
    {
      case '-':
      {
	/* try a range of absolute date minus offset of Ndwmy */
	pt = get_offset (min, pc, -1);
	if (pc == pt)
	{
	  if (flag == MUTT_PDR_NONE)
	  { /* nothing yet and no offset parsed => absolute date? */
	    if (!getDate (pc, max, err))
	      flag |= (MUTT_PDR_ABSOLUTE | MUTT_PDR_ERRORDONE);  /* done bad */
	    else
	    {
	      /* reestablish initial base minimum if not specified */
	      if (!haveMin)
		memcpy (min, baseMin, sizeof(struct tm));
	      flag |= (MUTT_PDR_ABSOLUTE | MUTT_PDR_DONE);  /* done good */
	    }
	  }
	  else
	    flag |= MUTT_PDR_ERRORDONE;
	}
	else
	{
	  pc = pt;
	  if (flag == MUTT_PDR_NONE && !haveMin)
	  { /* the very first "-3d" without a previous absolute date */
	    max->tm_year = min->tm_year;
	    max->tm_mon = min->tm_mon;
	    max->tm_mday = min->tm_mday;
	  }
	  flag |= MUTT_PDR_MINUS;
	}
      }
      break;
      case '+':
      { /* enlarge plusRange */
	pt = get_offset (max, pc, 1);
	if (pc == pt)
	  flag |= MUTT_PDR_ERRORDONE;
	else
	{
	  pc = pt;
	  flag |= MUTT_PDR_PLUS;
	}
      }
      break;
      case '*':
      { /* enlarge window in both directions */
	pt = get_offset (min, pc, -1);
	if (pc == pt)
	  flag |= MUTT_PDR_ERRORDONE;
	else
	{
	  pc = get_offset (max, pc, 1);
	  flag |= MUTT_PDR_WINDOW;
	}
      }
      break;
      default:
	flag |= MUTT_PDR_ERRORDONE;
    }
    SKIPWS (pc);
  }
  if ((flag & MUTT_PDR_ERROR) && !(flag & MUTT_PDR_ABSOLUTE))
  { /* getDate has its own error message, don't overwrite it here */
    snprintf (err->data, err->dsize, _("Invalid relative date: %s"), pc-1);
  }
  return ((flag & MUTT_PDR_ERROR) ? NULL : pc);
}