static void mutt_restore_default (struct option_t *p)
{
  switch (p->type & DT_MASK)
  {
    case DT_STR:
      if (p->init)
	mutt_str_replace ((char **) p->data, (char *) p->init); 
      break;
    case DT_PATH:
      if (p->init)
      {
	char path[_POSIX_PATH_MAX];

	strfcpy (path, (char *) p->init, sizeof (path));
	mutt_expand_path (path, sizeof (path));
	mutt_str_replace ((char **) p->data, path);
      }
      break;
    case DT_ADDR:
      if (p->init)
      {
	rfc822_free_address ((ADDRESS **) p->data);
	*((ADDRESS **) p->data) = rfc822_parse_adrlist (NULL, (char *) p->init);
      }
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
	  if (mutt_strcmp (p->option, "alternates") == 0)
	    flags |= REG_ICASE;
	  else if (mutt_strcmp (p->option, "mask") != 0)
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
	    regfree (pp->rx);
	    FREE (&pp->rx);
	  }
	}
      }
      break;
  }

  if (p->flags & R_INDEX)
    set_option (OPTFORCEREDRAWINDEX);
  if (p->flags & R_PAGER)
    set_option (OPTFORCEREDRAWPAGER);
  if (p->flags & R_RESORT_SUB)
    set_option (OPTSORTSUBTHREADS);
  if (p->flags & R_RESORT)
    set_option (OPTNEEDRESORT);
  if (p->flags & R_RESORT_INIT)
    set_option (OPTRESORTINIT);
}