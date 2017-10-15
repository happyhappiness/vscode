static pgp_key_t pgp_select_key (pgp_key_t keys,
                                 ADDRESS * p, const char *s)
{
  int keymax;
  pgp_uid_t **KeyTable;
  MUTTMENU *menu;
  int i, done = 0;
  char helpstr[LONG_STRING], buf[LONG_STRING], tmpbuf[STRING];
  char cmd[LONG_STRING], tempfile[_POSIX_PATH_MAX];
  FILE *fp, *devnull;
  pid_t thepid;
  pgp_key_t kp;
  pgp_uid_t *a;
  int (*f) (const void *, const void *);

  int unusable = 0;

  keymax = 0;
  KeyTable = NULL;

  for (i = 0, kp = keys; kp; kp = kp->next)
  {
    if (!option (OPTPGPSHOWUNUSABLE) && (kp->flags & KEYFLAG_CANTUSE))
    {
      unusable = 1;
      continue;
    }

    for (a = kp->address; a; a = a->next)
    {
      if (!option (OPTPGPSHOWUNUSABLE) && (a->flags & KEYFLAG_CANTUSE))
      {
	unusable = 1;
	continue;
      }

      if (i == keymax)
      {
	keymax += 5;
	safe_realloc (&KeyTable, sizeof (pgp_uid_t *) * keymax);
      }

      KeyTable[i++] = a;
    }
  }

  if (!i && unusable)
  {
    mutt_error _("All matching keys are expired, revoked, or disabled.");
    mutt_sleep (1);
    return NULL;
  }

  switch (PgpSortKeys & SORT_MASK)
  {
    case SORT_DATE:
      f = pgp_compare_date;
      break;
    case SORT_KEYID:
      f = pgp_compare_keyid;
      break;
    case SORT_ADDRESS:
      f = pgp_compare_address;
      break;
    case SORT_TRUST:
    default:
      f = pgp_compare_trust;
      break;
  }
  qsort (KeyTable, i, sizeof (pgp_uid_t *), f);

  helpstr[0] = 0;
  mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_PGP, OP_EXIT);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Select  "), MENU_PGP,
		  OP_GENERIC_SELECT_ENTRY);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Check key  "), MENU_PGP, OP_VERIFY_KEY);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Help"), MENU_PGP, OP_HELP);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */

  menu = mutt_new_menu (MENU_PGP);
  menu->max = i;
  menu->make_entry = pgp_entry;
  menu->help = helpstr;
  menu->data = KeyTable;

  if (p)
    snprintf (buf, sizeof (buf), _("PGP keys matching <%s>."), p->mailbox);
  else
    snprintf (buf, sizeof (buf), _("PGP keys matching \"%s\"."), s);


  menu->title = buf;

  kp = NULL;

  mutt_clear_error ();

  while (!done)
  {
    switch (mutt_menuLoop (menu))
    {

    case OP_VERIFY_KEY:

      mutt_mktemp (tempfile, sizeof (tempfile));
      if ((devnull = fopen ("/dev/null", "w")) == NULL)	/* __FOPEN_CHECKED__ */
      {
	mutt_perror _("Can't open /dev/null");
	break;
      }
      if ((fp = safe_fopen (tempfile, "w")) == NULL)
      {
	safe_fclose (&devnull);
	mutt_perror _("Can't create temporary file");
	break;
      }

      mutt_message _("Invoking PGP...");

      snprintf (tmpbuf, sizeof (tmpbuf), "0x%s",
          pgp_fpr_or_lkeyid (pgp_principal_key (KeyTable[menu->current]->parent)));

      if ((thepid = pgp_invoke_verify_key (NULL, NULL, NULL, -1,
		    fileno (fp), fileno (devnull), tmpbuf)) == -1)
      {
	mutt_perror _("Can't create filter");
	unlink (tempfile);
	safe_fclose (&fp);
	safe_fclose (&devnull);
      }

      mutt_wait_filter (thepid);
      safe_fclose (&fp);
      safe_fclose (&devnull);
      mutt_clear_error ();
      snprintf (cmd, sizeof (cmd), _("Key ID: 0x%s"), 
		pgp_keyid (pgp_principal_key (KeyTable[menu->current]->parent)));
      mutt_do_pager (cmd, tempfile, 0, NULL);
      menu->redraw = REDRAW_FULL;

      break;

    case OP_VIEW_ID:

      mutt_message ("%s", NONULL (KeyTable[menu->current]->addr));
      break;

    case OP_GENERIC_SELECT_ENTRY:


      /* XXX make error reporting more verbose */

      if (option (OPTPGPCHECKTRUST))
	if (!pgp_key_is_valid (KeyTable[menu->current]->parent))
	{
	  mutt_error _("This key can't be used: expired/disabled/revoked.");
	  break;
	}

      if (option (OPTPGPCHECKTRUST) &&
	  (!pgp_id_is_valid (KeyTable[menu->current])
	   || !pgp_id_is_strong (KeyTable[menu->current])))
      {
	char *s = "";
	char buff[LONG_STRING];
	
	if (KeyTable[menu->current]->flags & KEYFLAG_CANTUSE)
	  s = N_("ID is expired/disabled/revoked.");
	else switch (KeyTable[menu->current]->trust & 0x03)
	{
	  case 0:
	    s = N_("ID has undefined validity.");
	    break;
	  case 1:
	    s = N_("ID is not valid.");
	    break;
	  case 2:
	    s = N_("ID is only marginally valid.");
	    break;
	}

	snprintf (buff, sizeof (buff), _("%s Do you really want to use the key?"),
		  _(s));

	if (mutt_yesorno (buff, M_NO) != M_YES)
	{
	  mutt_clear_error ();
	  break;
	}
      }

# if 0
      kp = pgp_principal_key (KeyTable[menu->current]->parent);
# else
      kp = KeyTable[menu->current]->parent;
# endif
      done = 1;
      break;

    case OP_EXIT:

      kp = NULL;
      done = 1;
      break;
    }
  }

  mutt_menuDestroy (&menu);
  FREE (&KeyTable);

  set_option (OPTNEEDREDRAW);

  return (kp);
}