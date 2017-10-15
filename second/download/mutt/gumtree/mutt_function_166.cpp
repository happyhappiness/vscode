static smime_key_t *smime_select_key (smime_key_t *keys, char *query)
{
  smime_key_t **table = NULL;
  int table_size = 0;
  int table_index = 0;
  smime_key_t *key = NULL;
  smime_key_t *selected_key = NULL;
  char helpstr[LONG_STRING];
  char buf[LONG_STRING];
  char title[256];
  MUTTMENU* menu;
  char *s = "";
  int done = 0;

  for (table_index = 0, key = keys; key; key = key->next)
  {
    if (table_index == table_size)
    {
      table_size += 5;
      safe_realloc (&table, sizeof (smime_key_t *) * table_size);
    }

    table[table_index++] = key;
  }

  snprintf(title, sizeof(title), _("S/MIME certificates matching \"%s\"."),
    query);

  /* Make Helpstring */
  helpstr[0] = 0;
  mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_SMIME, OP_EXIT);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof (buf), _("Select  "), MENU_SMIME,
      OP_GENERIC_SELECT_ENTRY);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
  mutt_make_help (buf, sizeof(buf), _("Help"), MENU_SMIME, OP_HELP);
  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */

  /* Create the menu */
  menu = mutt_new_menu(MENU_SMIME);
  menu->max = table_index;
  menu->make_entry = smime_entry;
  menu->help = helpstr;
  menu->data = table;
  menu->title = title;
  /* sorting keys might be done later - TODO */

  mutt_clear_error();

  done = 0;
  while (!done)
  {
    switch (mutt_menuLoop (menu))
    {
      case OP_GENERIC_SELECT_ENTRY:
        if (table[menu->current]->trust != 't')
        {
          switch (table[menu->current]->trust)
          {
            case 'i':
            case 'r':
            case 'e':
              s = N_("ID is expired/disabled/revoked.");
              break;
            case 'u':
              s = N_("ID has undefined validity.");
              break;
            case 'v':
              s = N_("ID is not trusted.");
              break;
          }

          snprintf (buf, sizeof (buf), _("%s Do you really want to use the key?"),
                    _(s));

          if (mutt_yesorno (buf, M_NO) != M_YES)
          {
            mutt_clear_error ();
            break;
          }
        }

        selected_key = table[menu->current];
        done = 1;
        break;
      case OP_EXIT:
        done = 1;
        break;
    }
  }

  mutt_menuDestroy (&menu);
  FREE (&table);
  set_option (OPTNEEDREDRAW);

  return selected_key;
}