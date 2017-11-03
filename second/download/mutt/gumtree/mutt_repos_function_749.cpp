static crypt_key_t *crypt_select_key (crypt_key_t *keys,
                                      ADDRESS * p, const char *s, 
                                      unsigned int app, int *forced_valid)
{
  int keymax;
  crypt_key_t **key_table;
  MUTTMENU *menu;
  int i, done = 0;
  char helpstr[LONG_STRING], buf[LONG_STRING];
  crypt_key_t *k;
  int (*f) (const void *, const void *);
  int menu_to_use = 0;
  int unusable = 0;

  *forced_valid = 0;

  /* build the key table */
  keymax = i = 0;
  key_table = NULL;
  for (k = keys; k; k = k->next)
    {
      if (!option (OPTPGPSHOWUNUSABLE) && (k->flags & KEYFLAG_CANTUSE))
        {
          unusable = 1;
          continue;
        }
      
      if (i == keymax)
        {
          keymax += 20;
          safe_realloc (&key_table, sizeof (crypt_key_t*)*keymax);
        }
      
      key_table[i++] = k;
    }

  if (!i && unusable)
    {
      mutt_error _("All matching keys are marked expired/revoked.");
      mutt_sleep (1);
      return NULL;
    }

  switch (PgpSortKeys & SORT_MASK)
  {
    case SORT_DATE:
      f = crypt_compare_date;
      break;
    case SORT_KEYID:
      f = crypt_compare_keyid;
      break;
    case SORT_ADDRESS:
      f = crypt_compare_address;
      break;
    case SORT_TRUST:
    default:
      f = crypt_compare_trust;
      break;
  }
  qsort (key_table, i, sizeof (crypt_key_t*), f);

  if (app & APPLICATION_PGP)
    menu_to_use = MENU_KEY_SELECT_PGP;
  else if (app & APPLICATION_SMIME)
    menu_to_use = MENU_KEY_SELECT_SMIME;

  helpstr[0] = 0;
  mutt_make_help (buf, sizeof (buf), _("Exit  "), menu_to_use, OP_EXIT);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Select  "), menu_to_use,
		  OP_GENERIC_SELECT_ENTRY);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Check key  "),
                  menu_to_use, OP_VERIFY_KEY);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Help"), menu_to_use, OP_HELP);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */

  menu = mutt_new_menu (menu_to_use);
  menu->max = i;
  menu->make_entry = crypt_entry;
  menu->help = helpstr;
  menu->data = key_table;

  {
    const char *ts;

    if ((app & APPLICATION_PGP) && (app &  APPLICATION_SMIME))
      ts = _("PGP and S/MIME keys matching");
    else if ((app & APPLICATION_PGP))
      ts = _("PGP keys matching");
    else if ((app & APPLICATION_SMIME))
      ts = _("S/MIME keys matching");
    else
      ts = _("keys matching");

    if (p)
      /* L10N:
         %1$s is one of the previous four entries.
         %2$s is an address.
         e.g. "S/MIME keys matching <me@mutt.org>." */
      snprintf (buf, sizeof (buf), _("%s <%s>."), ts, p->mailbox);
    else
      /* L10N:
         e.g. 'S/MIME keys matching "Michael Elkins".' */
      snprintf (buf, sizeof (buf), _("%s \"%s\"."), ts, s);
    menu->title = buf; 
  }

  mutt_clear_error ();
  k = NULL;
  while (!done)
    {
      *forced_valid = 0;
      switch (mutt_menuLoop (menu))
        {
        case OP_VERIFY_KEY:
          verify_key (key_table[menu->current]);
          menu->redraw = REDRAW_FULL;
          break;
          
        case OP_VIEW_ID:
          mutt_message ("%s", key_table[menu->current]->uid);
          break;
          
        case OP_GENERIC_SELECT_ENTRY:
          /* FIXME make error reporting more verbose - this should be
             easy because gpgme provides more information */
          if (option (OPTPGPCHECKTRUST))
            {
            if (!crypt_key_is_valid (key_table[menu->current]))
              {
                mutt_error _("This key can't be used: "
                             "expired/disabled/revoked.");
                break;
              }
            }
          
          if (option (OPTPGPCHECKTRUST) &&
              (!crypt_id_is_valid (key_table[menu->current])
               || !crypt_id_is_strong (key_table[menu->current])))
            {
              const char *warn_s;
              char buff[LONG_STRING];
              
              if (key_table[menu->current]->flags & KEYFLAG_CANTUSE)
                warn_s = N_("ID is expired/disabled/revoked.");
              else 
                {
                  warn_s = "??";
                  switch (key_table[menu->current]->validity)
                    {
                    case GPGME_VALIDITY_UNKNOWN:   
                    case GPGME_VALIDITY_UNDEFINED: 
                      warn_s = N_("ID has undefined validity.");
                      break;
                    case GPGME_VALIDITY_NEVER:     
                      warn_s = N_("ID is not valid.");
                      break;
                    case GPGME_VALIDITY_MARGINAL:  
                      warn_s = N_("ID is only marginally valid.");
                      break;
                    case GPGME_VALIDITY_FULL:      
                    case GPGME_VALIDITY_ULTIMATE:  
                      break;
                    }
                }

              snprintf (buff, sizeof (buff),
                        _("%s Do you really want to use the key?"),
                        _(warn_s));
              
              if (mutt_yesorno (buff, 0) != 1)
                {
                  mutt_clear_error ();
                  break;
                }
              *forced_valid = 1;
            }  

          k = crypt_copy_key (key_table[menu->current]);
          done = 1;
          break;
          
        case OP_EXIT:
          k = NULL;
          done = 1;
          break;
        }
    }
  
  mutt_menuDestroy (&menu);
  FREE (&key_table);

  set_option (OPTNEEDREDRAW);
  
  return k;
}