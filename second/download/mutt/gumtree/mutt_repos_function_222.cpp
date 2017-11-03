int mutt_select_sort (int reverse)
{
  int method = Sort; /* save the current method in case of abort */

  switch (mutt_multi_choice (reverse ?
			     _("Rev-Sort (d)ate/(f)rm/(r)ecv/(s)ubj/t(o)/(t)hread/(u)nsort/si(z)e/s(c)ore/s(p)am?: ") :
			     _("Sort (d)ate/(f)rm/(r)ecv/(s)ubj/t(o)/(t)hread/(u)nsort/si(z)e/s(c)ore/s(p)am?: "),
			     _("dfrsotuzcp")))
  {
  case -1: /* abort - don't resort */
    return -1;

  case 1: /* (d)ate */
    Sort = SORT_DATE;
    break;

  case 2: /* (f)rm */
    Sort = SORT_FROM;
    break;
  
  case 3: /* (r)ecv */
    Sort = SORT_RECEIVED;
    break;
  
  case 4: /* (s)ubj */
    Sort = SORT_SUBJECT;
    break;
  
  case 5: /* t(o) */
    Sort = SORT_TO;
    break;
  
  case 6: /* (t)hread */
    Sort = SORT_THREADS;
    break;
  
  case 7: /* (u)nsort */
    Sort = SORT_ORDER;
    break;
  
  case 8: /* si(z)e */
    Sort = SORT_SIZE;
    break;
  
  case 9: /* s(c)ore */ 
    Sort = SORT_SCORE;
    break;

  case 10: /* s(p)am */
    Sort = SORT_SPAM;
    break;
  }
  if (reverse)
    Sort |= SORT_REVERSE;

  return (Sort != method ? 0 : -1); /* no need to resort if it's the same */
}