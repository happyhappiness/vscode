static void mutt_restore_default (struct option_t *p)
{
  switch (p->type & DT_MASK)
  {
    case DT_STR:
      mutt_str_replace ((char **) p->data, (char *) p->init); 
      break;
    case DT_MBCHARTBL:
      free_mbchar_table ((mbchar_table **)p->data);
      *((mbchar_table **) p->data) = parse_mbchar_table ((char *) p->init);
      break;
    case DT_PATH:
      FREE((char **) p->data);		/* __FREE_CHECKED__ */
      if (p->init)
      {
	char path[_POSIX_PATH_MAX];
	strfcpy (path, (char *) p->init, sizeof (path));
	mutt_expand_path (path, sizeof (path));
	*((char **) p->data) = safe_strdup (path);
      }
      break;
    case DT_ADDR:
      rfc822_free_address ((ADDRESS **) p->data);
      if (p->init)
	*((ADDRESS **) p->data) = rfc822_parse_adrlist (NULL, (char *) p->init);
      break;
    case DT_BOOL:
      if (p->init)
	set_option (p->data);
      else
	unset_option (p->data);
      break;
    case DT_QUAD:
      set_quadoption (p->data, p->init);
      break;
    case DT_NUM:
    case DT_SORT:
    case DT_MAGIC:
      *((short *) p->data) = p->init;
      break;
    case DT_RX:
      {
	REGEXP *pp = (REGEXP *) p->data;
	int flags = 0;

	FREE (&pp->pattern);
	if (pp->rx)
	{
	  regfree (pp->rx);
	  FREE (&pp->rx);
	}

	if (p->init)
	{
	  char *s = (char *) p->init;

	  pp->rx = safe_calloc (1, sizeof (regex_t));
	  pp->pattern = safe_strdup ((char *) p->init);
	  if (mutt_strcmp (p->option, "mask") != 0)
	    flags |= mutt_which_case ((const char *) p->init);
	  if (mutt_strcmp (p->option, "mask") == 0 && *s == '!')
	  {
	    s++;
	    pp->not = 1;
	  }
	  if (REGCOMP (pp->rx, s, flags) != 0)
	  {
	    fprintf (stderr, _("mutt_restore_default(%s): error in regexp: %s\n"),
		     p->option, pp->pattern);
	    FREE (&pp->pattern);
	    FREE (&pp->rx);
	  }
	}
      }
      break;
  }

  if (p->flags & R_INDEX)
    mutt_set_menu_redraw_full (MENU_MAIN);
  if (p->flags & R_PAGER)
    mutt_set_menu_redraw_full (MENU_PAGER);
  if (p->flags & R_PAGER_FLOW)
  {
    mutt_set_menu_redraw_full (MENU_PAGER);
    mutt_set_menu_redraw (MENU_PAGER, REDRAW_FLOW);
  }
  if (p->flags & R_RESORT_SUB)
    set_option (OPTSORTSUBTHREADS);
  if (p->flags & R_RESORT)
    set_option (OPTNEEDRESORT);
  if (p->flags & R_RESORT_INIT)
    set_option (OPTRESORTINIT);
  if (p->flags & R_TREE)
    set_option (OPTREDRAWTREE);
  if (p->flags & R_REFLOW)
    mutt_reflow_windows ();
#ifdef USE_SIDEBAR
  if (p->flags & R_SIDEBAR)
    mutt_set_current_menu_redraw (REDRAW_SIDEBAR);
#endif
  if (p->flags & R_MENU)
    mutt_set_current_menu_redraw_full ();
}