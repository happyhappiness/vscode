    case 'i':
      truststate = N_("Invalid   ");
      break;
    default:
      truststate = N_("Unknown   ");
  }
  snprintf(s, l, " 0x%s %s %s %-35.35s %s", this->hash,
           smime_key_flags (this->flags), truststate, this->email, this->label);
}


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

static smime_key_t *smime_parse_key(char *buf)
{
  smime_key_t *key;
  char *pend, *p;
  int field = 0;

  key = safe_calloc (sizeof (smime_key_t), 1);

  for (p = buf; p; p = pend)
  {
    if ((pend = strchr (p, ' ')) || (pend = strchr (p, '\n')))
      *pend++ = 0;

    /* For backward compatibility, don't count consecutive delimiters
     * as an empty field.
     */
    if (!*p)
      continue;

    field++;

    switch (field)
    {
      case 1:                   /* mailbox */
        key->email = safe_strdup (p);
        break;
      case 2:                   /* hash */
        key->hash = safe_strdup (p);
        break;
      case 3:                   /* label */
        key->label = safe_strdup (p);
        break;
      case 4:                   /* issuer */
        key->issuer = safe_strdup (p);
        break;
      case 5:                   /* trust */
        key->trust = *p;
        break;
      case 6:                   /* purpose */
        while (*p)
        {
          switch (*p++)
          {
            case 'e':
              key->flags |= KEYFLAG_CANENCRYPT;
              break;

            case 's':
              key->flags |= KEYFLAG_CANSIGN;
              break;
          }
        }
        break;
    }
  }

  /* Old index files could be missing issuer, trust, and purpose,
   * but anything less than that is an error. */
  if (field < 3)
  {
    smime_free_key (&key);
    return NULL;
  }

  if (field < 4)
    key->issuer = safe_strdup ("?");

  if (field < 5)
    key->trust = 't';

  if (field < 6)
    key->flags = (KEYFLAG_CANENCRYPT | KEYFLAG_CANSIGN);

  return key;
}

static smime_key_t *smime_get_candidates(char *search, short public)
{
  char index_file[_POSIX_PATH_MAX];
  FILE *fp;
  char buf[LONG_STRING];
  smime_key_t *key, *results, **results_end;

  results = NULL;
  results_end = &results;

  snprintf(index_file, sizeof (index_file), "%s/.index",
    public ? NONULL(SmimeCertificates) : NONULL(SmimeKeys));

  if ((fp = safe_fopen (index_file, "r")) == NULL)
  {
    mutt_perror (index_file);
    return NULL;
  }

  while (fgets (buf, sizeof (buf), fp))
  {
    if ((! *search) || mutt_stristr (buf, search))
    {
      key = smime_parse_key (buf);
      if (key)
      {
        *results_end = key;
        results_end = &key->next;
      }
    }
  }

  safe_fclose (&fp);

  return results;
}

/* Returns the first matching key record, without prompting or checking of
 * abilities or trust.
 */
static smime_key_t *smime_get_key_by_hash(char *hash, short public)
{
  smime_key_t *results, *result;
  smime_key_t *match = NULL;

  results = smime_get_candidates(hash, public);
  for (result = results; result; result = result->next)
  {
    if (mutt_strcasecmp (hash, result->hash) == 0)
    {
      match = smime_copy_key (result);
      break;
    }
  }

  smime_free_key (&results);

  return match;
}

static smime_key_t *smime_get_key_by_addr(char *mailbox, short abilities, short public, short may_ask)
{
  smime_key_t *results, *result;
  smime_key_t *matches = NULL;
  smime_key_t **matches_end = &matches;
  smime_key_t *match;
  smime_key_t *trusted_match = NULL;
  smime_key_t *valid_match = NULL;
  smime_key_t *return_key = NULL;
  int multi_trusted_matches = 0;

  if (! mailbox)
    return NULL;

  results = smime_get_candidates(mailbox, public);
  for (result = results; result; result = result->next)
  {
    if (abilities && !(result->flags & abilities))
    {
      continue;
    }

    if (mutt_strcasecmp (mailbox, result->email) == 0)
    {
      match = smime_copy_key (result);
      *matches_end = match;
      matches_end = &match->next;

      if (match->trust == 't')
      {
        if (trusted_match &&
            (mutt_strcasecmp (match->hash, trusted_match->hash) != 0))
	{
          multi_trusted_matches = 1;
	}
        trusted_match = match;
      }
      else if ((match->trust == 'u') || (match->trust == 'v'))
      {
        valid_match = match;
      }
    }
  }

  smime_free_key (&results);

  if (matches)
  {
    if (! may_ask)
    {
      if (trusted_match)
        return_key = smime_copy_key (trusted_match);
      else if (valid_match)
        return_key = smime_copy_key (valid_match);
      else
        return_key = NULL;
    }
    else if (trusted_match && !multi_trusted_matches)
    {
      return_key = smime_copy_key (trusted_match);
    }
    else
    {
      return_key = smime_copy_key (smime_select_key (matches, mailbox));
    }

    smime_free_key (&matches);
  }

  return return_key;
}

static smime_key_t *smime_get_key_by_str(char *str, short abilities, short public)
{
  smime_key_t *results, *result;
  smime_key_t *matches = NULL;
  smime_key_t **matches_end = &matches;
  smime_key_t *match;
  smime_key_t *return_key = NULL;

  if (! str)
    return NULL;

  results = smime_get_candidates(str, public);
  for (result = results; result; result = result->next)
  {
    if (abilities && !(result->flags & abilities))
    {
      continue;
    }

    if ((mutt_strcasecmp (str, result->hash) == 0) ||
        mutt_stristr(result->email, str) ||
        mutt_stristr(result->label, str))
    {
      match = smime_copy_key (result);
      *matches_end = match;
      matches_end = &match->next;
    }
  }

  smime_free_key (&results);

  if (matches)
  {
    return_key = smime_copy_key (smime_select_key (matches, str));
    smime_free_key (&matches);
  }

  return return_key;
}


smime_key_t *smime_ask_for_key(char *prompt, short abilities, short public)
{
  smime_key_t *key;
  char resp[SHORT_STRING];

  if (!prompt) prompt = _("Enter keyID: ");

  mutt_clear_error ();

  FOREVER
  {
    resp[0] = 0;
    if (mutt_get_field (prompt, resp, sizeof (resp), M_CLEAR) != 0)
      return NULL;

    if ((key = smime_get_key_by_str (resp, abilities, public)))
      return key;

    BEEP ();
  }
}



/* 
   This sets the '*ToUse' variables for an upcoming decryption, where
   the required key is different from SmimeDefaultKey.
*/

void _smime_getkeys (char *mailbox)
{
  smime_key_t *key = NULL;
  char *k = NULL;
  char buf[STRING];

  key = smime_get_key_by_addr (mailbox, KEYFLAG_CANENCRYPT, 0, 1);

  if (!key)
  {
    snprintf(buf, sizeof(buf), _("Enter keyID for %s: "),
	     mailbox);
    key = smime_ask_for_key (buf, KEYFLAG_CANENCRYPT, 0);
  }

  if (key)
  {
    k = key->hash;

    /* the key used last time. */
    if (*SmimeKeyToUse && 
        !mutt_strcasecmp (k, SmimeKeyToUse + mutt_strlen (SmimeKeys)+1))
    {
      smime_free_key (&key);
      return;
    }
    else smime_void_passphrase ();

    snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	      NONULL(SmimeKeys), k);
