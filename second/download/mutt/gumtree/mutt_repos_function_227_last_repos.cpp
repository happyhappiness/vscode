int mutt_select_sort (int reverse)
{
  int method = Sort; /* save the current method in case of abort */

  switch (mutt_multi_choice (reverse ?
       /* L10N: The following three are the sort/reverse sort prompts.
        * Letters must match the order of the characters in the third
        * string.  Note that mutt now supports multiline prompts, so
        * it's okay for the translation to take up to three lines.
        */
	_("Rev-Sort Date/Frm/Recv/Subj/tO/Thread/Unsort/siZe/sCore/sPam/Label?: ") :
	_("Sort Date/Frm/Recv/Subj/tO/Thread/Unsort/siZe/sCore/sPam/Label?: "),
	_("dfrsotuzcpl")))
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

  case 11: /* (l)abel */
    Sort = SORT_LABEL;
    break;
  }
  if (reverse)
    Sort |= SORT_REVERSE;

  return (Sort != method ? 0 : -1); /* no need to resort if it's the same */
}