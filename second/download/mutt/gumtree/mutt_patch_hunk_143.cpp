     case 'i':
       truststate = N_("Invalid   ");
       break;
     default:
       truststate = N_("Unknown   ");
   }
-  if (this.public)
-    snprintf(s, l, " 0x%.8X.%i %s %-35.35s %s", this.hash, this.suffix, truststate, this.email, this.nick);
-  else
-    snprintf(s, l, " 0x%.8X.%i %-35.35s %s", this.hash, this.suffix, this.email, this.nick);
+  snprintf(s, l, " 0x%s %s %s %-35.35s %s", this->hash,
+           smime_key_flags (this->flags), truststate, this->email, this->label);
 }
 
 
+static smime_key_t *smime_select_key (smime_key_t *keys, char *query)
+{
+  smime_key_t **table = NULL;
+  int table_size = 0;
+  int table_index = 0;
+  smime_key_t *key = NULL;
+  smime_key_t *selected_key = NULL;
+  char helpstr[LONG_STRING];
+  char buf[LONG_STRING];
+  char title[256];
+  MUTTMENU* menu;
+  char *s = "";
+  int done = 0;
+
+  for (table_index = 0, key = keys; key; key = key->next)
+  {
+    if (table_index == table_size)
+    {
+      table_size += 5;
+      safe_realloc (&table, sizeof (smime_key_t *) * table_size);
+    }
+
+    table[table_index++] = key;
+  }
+
+  snprintf(title, sizeof(title), _("S/MIME certificates matching \"%s\"."),
+    query);
+
+  /* Make Helpstring */
+  helpstr[0] = 0;
+  mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_SMIME, OP_EXIT);
+  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
+  mutt_make_help (buf, sizeof (buf), _("Select  "), MENU_SMIME,
+      OP_GENERIC_SELECT_ENTRY);
+  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
+  mutt_make_help (buf, sizeof(buf), _("Help"), MENU_SMIME, OP_HELP);
+  strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
+
+  /* Create the menu */
+  menu = mutt_new_menu(MENU_SMIME);
+  menu->max = table_index;
+  menu->make_entry = smime_entry;
+  menu->help = helpstr;
+  menu->data = table;
+  menu->title = title;
+  /* sorting keys might be done later - TODO */
+
+  mutt_clear_error();
+
+  done = 0;
+  while (!done)
+  {
+    switch (mutt_menuLoop (menu))
+    {
+      case OP_GENERIC_SELECT_ENTRY:
+        if (table[menu->current]->trust != 't')
+        {
+          switch (table[menu->current]->trust)
+          {
+            case 'i':
+            case 'r':
+            case 'e':
+              s = N_("ID is expired/disabled/revoked.");
+              break;
+            case 'u':
+              s = N_("ID has undefined validity.");
+              break;
+            case 'v':
+              s = N_("ID is not trusted.");
+              break;
+          }
+
+          snprintf (buf, sizeof (buf), _("%s Do you really want to use the key?"),
+                    _(s));
+
+          if (mutt_yesorno (buf, M_NO) != M_YES)
+          {
+            mutt_clear_error ();
+            break;
+          }
+        }
+
+        selected_key = table[menu->current];
+        done = 1;
+        break;
+      case OP_EXIT:
+        done = 1;
+        break;
+    }
+  }
+
+  mutt_menuDestroy (&menu);
+  FREE (&table);
+  set_option (OPTNEEDREDRAW);
+
+  return selected_key;
+}
+
+static smime_key_t *smime_parse_key(char *buf)
+{
+  smime_key_t *key;
+  char *pend, *p;
+  int field = 0;
+
+  key = safe_calloc (sizeof (smime_key_t), 1);
+
+  for (p = buf; p; p = pend)
+  {
+    if ((pend = strchr (p, ' ')) || (pend = strchr (p, '\n')))
+      *pend++ = 0;
+
+    /* For backward compatibility, don't count consecutive delimiters
+     * as an empty field.
+     */
+    if (!*p)
+      continue;
+
+    field++;
 
+    switch (field)
+    {
+      case 1:                   /* mailbox */
+        key->email = safe_strdup (p);
+        break;
+      case 2:                   /* hash */
+        key->hash = safe_strdup (p);
+        break;
+      case 3:                   /* label */
+        key->label = safe_strdup (p);
+        break;
+      case 4:                   /* issuer */
+        key->issuer = safe_strdup (p);
+        break;
+      case 5:                   /* trust */
+        key->trust = *p;
+        break;
+      case 6:                   /* purpose */
+        while (*p)
+        {
+          switch (*p++)
+          {
+            case 'e':
+              key->flags |= KEYFLAG_CANENCRYPT;
+              break;
+
+            case 's':
+              key->flags |= KEYFLAG_CANSIGN;
+              break;
+          }
+        }
+        break;
+    }
+  }
 
+  /* Old index files could be missing issuer, trust, and purpose,
+   * but anything less than that is an error. */
+  if (field < 3)
+  {
+    smime_free_key (&key);
+    return NULL;
+  }
 
-char* smime_ask_for_key (char *prompt, char *mailbox, short public)
+  if (field < 4)
+    key->issuer = safe_strdup ("?");
+
+  if (field < 5)
+    key->trust = 't';
+
+  if (field < 6)
+    key->flags = (KEYFLAG_CANENCRYPT | KEYFLAG_CANSIGN);
+
+  return key;
+}
+
+static smime_key_t *smime_get_candidates(char *search, short public)
 {
-  char *fname;
-  smime_id *table = 0;
-  int table_count;
   char index_file[_POSIX_PATH_MAX];
-  FILE *index;
+  FILE *fp;
   char buf[LONG_STRING];
-  char fields[5][STRING+1]; /* +1 due to use of fscanf() below. the max field width does not include the null terminator (see http://dev.mutt.org/trac/ticket/3636) */
-  int numFields, hash_suffix, done, cur; /* The current entry */
-  MUTTMENU* menu;
-  unsigned int hash;
-  char helpstr[HUGE_STRING*3];
-  char qry[256];
-  char title[256];
+  smime_key_t *key, *results, **results_end;
+
+  results = NULL;
+  results_end = &results;
 
-  if (!prompt) prompt = _("Enter keyID: ");
   snprintf(index_file, sizeof (index_file), "%s/.index",
     public ? NONULL(SmimeCertificates) : NONULL(SmimeKeys));
-  
-  FOREVER
+
+  if ((fp = safe_fopen (index_file, "r")) == NULL)
   {
-    *qry = 0;
-    if (mutt_get_field(prompt,
-      qry, sizeof(qry), 0))
-      return NULL;
-    snprintf(title, sizeof(title), _("S/MIME certificates matching \"%s\"."),
-      qry);
+    mutt_perror (index_file);
+    return NULL;
+  }
 
-    
-    index = fopen(index_file, "r");
-    if (index == NULL) 
+  while (fgets (buf, sizeof (buf), fp))
+  {
+    if ((! *search) || mutt_stristr (buf, search))
     {
-      mutt_perror (index_file);      
-      return NULL;
-    }
-    /* Read Entries */
-    cur = 0;
-    table_count = 0;
-    while (!feof(index)) {
-        numFields = fscanf (index, MUTT_FORMAT(STRING) " %x.%i " MUTT_FORMAT(STRING), fields[0], &hash,
-          &hash_suffix, fields[2]);
-        if (public)
-          fscanf (index, MUTT_FORMAT(STRING) " " MUTT_FORMAT(STRING) "\n", fields[3], fields[4]);
-  
-      /* 0=email 1=name 2=nick 3=intermediate 4=trust */
-      if (numFields < 2) continue;
-  
-      /* Check if query matches this certificate */
-      if (!mutt_stristr(fields[0], qry) &&
-          !mutt_stristr(fields[2], qry))
-        continue;
-  
-      ++table_count;
-      safe_realloc(&table, sizeof(smime_id) * table_count);
-      table[cur].hash = hash;
-      table[cur].suffix = hash_suffix;
-      strncpy(table[cur].email, fields[0], sizeof(table[cur].email));
-      strncpy(table[cur].nick, fields[2], sizeof(table[cur].nick));
-      table[cur].trust = *fields[4];
-      table[cur].public = public;
-  
-      cur++;
-    }
-    safe_fclose (&index);
-  
-    /* Make Helpstring */
-    helpstr[0] = 0;
-    mutt_make_help (buf, sizeof (buf), _("Exit  "), MENU_SMIME, OP_EXIT);
-    strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
-    mutt_make_help (buf, sizeof (buf), _("Select  "), MENU_SMIME,
-        OP_GENERIC_SELECT_ENTRY);
-    strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
-    mutt_make_help (buf, sizeof(buf), _("Help"), MENU_SMIME, OP_HELP);
-    strcat (helpstr, buf);	/* __STRCAT_CHECKED__ */
-  
-    /* Create the menu */
-    menu = mutt_new_menu(MENU_SMIME);
-    menu->max = cur;
-    menu->make_entry = smime_entry;
-    menu->help = helpstr;
-    menu->data = table;
-    menu->title = title;
-    /* sorting keys might be done later - TODO */
-  
-    mutt_clear_error();
-  
-    done = 0;
-    hash = 0;
-    while (!done) {
-      switch (mutt_menuLoop (menu)) {
-        case OP_GENERIC_SELECT_ENTRY:
-          cur = menu->current;
-	  hash = 1;
-          done = 1;
-          break;
-        case OP_EXIT:
-          hash = 0;
-          done = 1;
-          break;
+      key = smime_parse_key (buf);
+      if (key)
+      {
+        *results_end = key;
+        results_end = &key->next;
       }
     }
-    if (table_count && hash)
-      safe_asprintf(&fname, "%.8x.%i", table[cur].hash, table[cur].suffix);
-    else fname = NULL;
-  
-    mutt_menuDestroy (&menu);
-    FREE (&table);
-    set_option (OPTNEEDREDRAW);
-  
-    if (fname) return fname;
   }
-}
 
+  safe_fclose (&fp);
 
+  return results;
+}
 
-char *smime_get_field_from_db (char *mailbox, char *query, short public, short may_ask)
+/* Returns the first matching key record, without prompting or checking of
+ * abilities or trust.
+ */
+static smime_key_t *smime_get_key_by_hash(char *hash, short public)
 {
-  int addr_len, query_len, found = 0, ask = 0, choice = 0;
-  char cert_path[_POSIX_PATH_MAX];
-  char buf[LONG_STRING], prompt[STRING];
-  char fields[5][STRING+1]; /* +1 due to use of fscanf() below. the max field width does not include the null terminator (see http://dev.mutt.org/trac/ticket/3636) */
-  char key[STRING];  
-  int numFields;
-  struct stat info;
-  char key_trust_level = 0;
-  FILE *fp;
+  smime_key_t *results, *result;
+  smime_key_t *match = NULL;
 
-  if(!mailbox && !query) return(NULL);
+  results = smime_get_candidates(hash, public);
+  for (result = results; result; result = result->next)
+  {
+    if (mutt_strcasecmp (hash, result->hash) == 0)
+    {
+      match = smime_copy_key (result);
+      break;
+    }
+  }
 
-  addr_len = mailbox ? mutt_strlen (mailbox) : 0;
-  query_len = query ? mutt_strlen (query) : 0;
-  
-  *key = '\0';
+  smime_free_key (&results);
 
-  /* index-file format:
-     mailbox certfile label issuer_certfile trust_flags\n
+  return match;
+}
 
-     certfile is a hash value generated by openssl.
-     Note that this was done according to the OpenSSL
-     specs on their CA-directory.
+static smime_key_t *smime_get_key_by_addr(char *mailbox, short abilities, short public, short may_ask)
+{
+  smime_key_t *results, *result;
+  smime_key_t *matches = NULL;
+  smime_key_t **matches_end = &matches;
+  smime_key_t *match;
+  smime_key_t *trusted_match = NULL;
+  smime_key_t *valid_match = NULL;
+  smime_key_t *return_key = NULL;
+  int multi_trusted_matches = 0;
 
-  */
-  snprintf (cert_path, sizeof (cert_path), "%s/.index",
-	    (public ? NONULL(SmimeCertificates) : NONULL(SmimeKeys)));
+  if (! mailbox)
+    return NULL;
 
-  if (!stat (cert_path, &info))
+  results = smime_get_candidates(mailbox, public);
+  for (result = results; result; result = result->next)
   {
-    if ((fp = safe_fopen (cert_path, "r")) == NULL)
+    if (abilities && !(result->flags & abilities))
     {
-      mutt_perror (cert_path);
-      return (NULL);
+      continue;
     }
 
-    while (fgets (buf, sizeof (buf) - 1, fp) != NULL)
-      if (mailbox && !(mutt_strncasecmp (mailbox, buf, addr_len)))
-      {
-	numFields = sscanf (buf, 
-			    MUTT_FORMAT(STRING) " " MUTT_FORMAT(STRING) " " 
-			    MUTT_FORMAT(STRING) " " MUTT_FORMAT(STRING) " " 
-			    MUTT_FORMAT(STRING) "\n", 
-			    fields[0], fields[1],
-			   fields[2], fields[3], 
-			    fields[4]);
-	if (numFields < 2)
-	    continue;
-	if (mailbox && public && 
-	    (*fields[4] == 'i' || *fields[4] == 'e' || *fields[4] == 'r'))
-	    continue;
+    if (mutt_strcasecmp (mailbox, result->email) == 0)
+    {
+      match = smime_copy_key (result);
+      *matches_end = match;
+      matches_end = &match->next;
 
-	if (found)
-	{
-	  if (public && *fields[4] == 'u' )
-	    snprintf (prompt, sizeof (prompt),
-		      _("ID %s is unverified. Do you want to use it for %s ?"),
-		      fields[1], mailbox);
-	  else if (public && *fields[4] == 'v' )
-	    snprintf (prompt, sizeof (prompt),
-		      _("Use (untrusted!) ID %s for %s ?"),
-		      fields[1], mailbox);
-	  else
-	    snprintf (prompt, sizeof (prompt), _("Use ID %s for %s ?"),
-		      fields[1], mailbox);
-	  if (may_ask == 0)
-	    choice = M_YES;
-	  if (may_ask && (choice = mutt_yesorno (prompt, M_NO)) == -1)
-	  {
-	    found = 0;
-	    ask = 0;
-	    *key = '\0';
-	    break;
-	  }
-	  else if (choice == M_NO) 
-	  {
-	    ask = 1;
-	    continue;
-	  }
-	  else if (choice == M_YES)
-	  {
-	    strfcpy (key, fields[1], sizeof (key));
-	    ask = 0;
-	    break;
-	  }
-	}
-	else
+      if (match->trust == 't')
+      {
+        if (trusted_match &&
+            (mutt_strcasecmp (match->hash, trusted_match->hash) != 0))
 	{
-	  if (public) 
-	    key_trust_level = *fields[4];
-	  strfcpy (key, fields[1], sizeof (key));
+          multi_trusted_matches = 1;
 	}
-	found = 1;
+        trusted_match = match;
       }
-      else if(query)
+      else if ((match->trust == 'u') || (match->trust == 'v'))
       {
-	numFields = sscanf (buf, 
-			    MUTT_FORMAT(STRING) " " MUTT_FORMAT(STRING) " " 
-			    MUTT_FORMAT(STRING) " " MUTT_FORMAT(STRING) " " 
-			    MUTT_FORMAT(STRING) "\n", 
-			    fields[0], fields[1],
-			    fields[2], fields[3], 
-			    fields[4]);
-
-	/* query = label: return certificate. */
-	if (numFields >= 3 && 
-	    !(mutt_strncasecmp (query, fields[2], query_len)))
-	{
-	  ask = 0;
-	  strfcpy (key, fields[1], sizeof (key));
-	}
-	/* query = certificate: return intermediate certificate. */
-	else if (numFields >= 4 && 
-		 !(mutt_strncasecmp (query, fields[1], query_len)))
-	{
-	  ask = 0;
-	  strfcpy (key, fields[3], sizeof (key));
-	}
+        valid_match = match;
       }
+    }
+  }
 
-    safe_fclose (&fp);
+  smime_free_key (&results);
 
-    if (ask)
+  if (matches)
+  {
+    if (! may_ask)
     {
-      if (public && *fields[4] == 'u' )
-	snprintf (prompt, sizeof (prompt),
-		  _("ID %s is unverified. Do you want to use it for %s ?"),
-		  fields[1], mailbox);
-      else if (public && *fields[4] == 'v' )
-	snprintf (prompt, sizeof (prompt),
-		  _("Use (untrusted!) ID %s for %s ?"),
-		  fields[1], mailbox);
+      if (trusted_match)
+        return_key = smime_copy_key (trusted_match);
+      else if (valid_match)
+        return_key = smime_copy_key (valid_match);
       else
-	snprintf (prompt, sizeof(prompt), _("Use ID %s for %s ?"), key,
-		  mailbox);
-      choice = mutt_yesorno (prompt, M_NO);
-      if (choice == -1 || choice == M_NO)
-	*key = '\0';
+        return_key = NULL;
     }
-    else if (key_trust_level && may_ask)
+    else if (trusted_match && !multi_trusted_matches)
     {
-      if (key_trust_level == 'u' )
-      {
-	snprintf (prompt, sizeof (prompt),
-		  _("ID %s is unverified. Do you want to use it for %s ?"),
-		  key, mailbox);
-	choice = mutt_yesorno (prompt, M_NO);
-	if (choice != M_YES)
-	  *key = '\0';
-      }
-      else if (key_trust_level == 'v' )
-      {
-	mutt_error (_("Warning: You have not yet decided to trust ID %s. (any key to continue)"), key);
-	mutt_sleep (5);
-      }
+      return_key = smime_copy_key (trusted_match);
+    }
+    else
+    {
+      return_key = smime_copy_key (smime_select_key (matches, mailbox));
     }
 
+    smime_free_key (&matches);
   }
 
-  /* Note: safe_strdup ("") returns NULL. */
-  return safe_strdup (key);
+  return return_key;
 }
 
+static smime_key_t *smime_get_key_by_str(char *str, short abilities, short public)
+{
+  smime_key_t *results, *result;
+  smime_key_t *matches = NULL;
+  smime_key_t **matches_end = &matches;
+  smime_key_t *match;
+  smime_key_t *return_key = NULL;
+
+  if (! str)
+    return NULL;
+
+  results = smime_get_candidates(str, public);
+  for (result = results; result; result = result->next)
+  {
+    if (abilities && !(result->flags & abilities))
+    {
+      continue;
+    }
+
+    if ((mutt_strcasecmp (str, result->hash) == 0) ||
+        mutt_stristr(result->email, str) ||
+        mutt_stristr(result->label, str))
+    {
+      match = smime_copy_key (result);
+      *matches_end = match;
+      matches_end = &match->next;
+    }
+  }
+
+  smime_free_key (&results);
+
+  if (matches)
+  {
+    return_key = smime_copy_key (smime_select_key (matches, str));
+    smime_free_key (&matches);
+  }
+
+  return return_key;
+}
+
+
+smime_key_t *smime_ask_for_key(char *prompt, short abilities, short public)
+{
+  smime_key_t *key;
+  char resp[SHORT_STRING];
+
+  if (!prompt) prompt = _("Enter keyID: ");
+
+  mutt_clear_error ();
+
+  FOREVER
+  {
+    resp[0] = 0;
+    if (mutt_get_field (prompt, resp, sizeof (resp), M_CLEAR) != 0)
+      return NULL;
+
+    if ((key = smime_get_key_by_str (resp, abilities, public)))
+      return key;
+
+    BEEP ();
+  }
+}
 
 
 
 /* 
    This sets the '*ToUse' variables for an upcoming decryption, where
    the required key is different from SmimeDefaultKey.
 */
 
 void _smime_getkeys (char *mailbox)
 {
+  smime_key_t *key = NULL;
   char *k = NULL;
   char buf[STRING];
 
-  k = smime_get_field_from_db (mailbox, NULL, 0, 1);
+  key = smime_get_key_by_addr (mailbox, KEYFLAG_CANENCRYPT, 0, 1);
 
-  if (!k)
+  if (!key)
   {
     snprintf(buf, sizeof(buf), _("Enter keyID for %s: "),
 	     mailbox);
-    k = smime_ask_for_key(buf, mailbox, 0);
+    key = smime_ask_for_key (buf, KEYFLAG_CANENCRYPT, 0);
   }
 
-  if (k)
+  if (key)
   {
+    k = key->hash;
+
     /* the key used last time. */
     if (*SmimeKeyToUse && 
         !mutt_strcasecmp (k, SmimeKeyToUse + mutt_strlen (SmimeKeys)+1))
     {
-      FREE (&k);
+      smime_free_key (&key);
       return;
     }
     else smime_void_passphrase ();
 
     snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
 	      NONULL(SmimeKeys), k);
