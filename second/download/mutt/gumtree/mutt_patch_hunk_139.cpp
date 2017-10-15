   t->subtype = safe_strdup ("pgp-signature");
   t->filename = safe_strdup (sigfile);
   t->use_disp = 0;
   t->disposition = DISPNONE;
   t->encoding = ENC7BIT;
   t->unlink = 1; /* ok to remove this file after sending. */
+  mutt_set_parameter ("name", "signature.asc", &t->parameter);
 
   return (a);
 }
 
-static short is_numerical_keyid (const char *s)
-{
-  /* or should we require the "0x"? */
-  if (strncmp (s, "0x", 2) == 0)
-    s += 2;
-  if (strlen (s) % 8)
-    return 0;
-  while (*s)
-    if (strchr ("0123456789ABCDEFabcdef", *s++) == NULL)
-      return 0;
-  
-  return 1;
-}
-
 /* This routine attempts to find the keyids of the recipients of a message.
  * It returns NULL if any of the keys can not be found.
+ * If oppenc_mode is true, only keys that can be determined without
+ * prompting will be used.
  */
-char *pgp_findKeys (ADDRESS *to, ADDRESS *cc, ADDRESS *bcc)
+char *pgp_findKeys (ADDRESS *adrlist, int oppenc_mode)
 {
+  LIST *crypt_hook_list, *crypt_hook = NULL;
   char *keyID, *keylist = NULL;
   size_t keylist_size = 0;
   size_t keylist_used = 0;
-  ADDRESS *tmp = NULL, *addr = NULL;
-  ADDRESS **last = &tmp;
+  ADDRESS *addr = NULL;
   ADDRESS *p, *q;
-  int i;
-  pgp_key_t k_info = NULL, key = NULL;
+  pgp_key_t k_info = NULL;
+  char buf[LONG_STRING];
+  int r;
+  int key_selected;
 
   const char *fqdn = mutt_fqdn (1);
 
-  for (i = 0; i < 3; i++) 
+  for (p = adrlist; p ; p = p->next)
   {
-    switch (i)
+    key_selected = 0;
+    crypt_hook_list = crypt_hook = mutt_crypt_hook (p);
+    do
     {
-      case 0: p = to; break;
-      case 1: p = cc; break;
-      case 2: p = bcc; break;
-      default: abort ();
-    }
-    
-    *last = rfc822_cpy_adr (p, 0);
-    while (*last)
-      last = &((*last)->next);
-  }
-
-  if (fqdn)
-    rfc822_qualify (tmp, fqdn);
-
-  tmp = mutt_remove_duplicates (tmp);
-  
-  for (p = tmp; p ; p = p->next)
-  {
-    char buf[LONG_STRING];
-
-    q = p;
-    k_info = NULL;
+      q = p;
+      k_info = NULL;
 
-    if ((keyID = mutt_crypt_hook (p)) != NULL)
-    {
-      int r;
-      snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
-      if ((r = mutt_yesorno (buf, M_YES)) == M_YES)
+      if (crypt_hook != NULL)
       {
-	if (is_numerical_keyid (keyID))
+        keyID = crypt_hook->data;
+        r = M_YES;
+        if (! oppenc_mode && option(OPTCRYPTCONFIRMHOOK))
 	{
-	  if (strncmp (keyID, "0x", 2) == 0)
-	    keyID += 2;
-	  goto bypass_selection;		/* you don't see this. */
+          snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
+          r = mutt_yesorno (buf, M_YES);
 	}
-	
-	/* check for e-mail address */
-	if (strchr (keyID, '@') && 
-	    (addr = rfc822_parse_adrlist (NULL, keyID)))
+        if (r == M_YES)
 	{
-	  if (fqdn) rfc822_qualify (addr, fqdn);
-	  q = addr;
+          if (crypt_is_numerical_keyid (keyID))
+          {
+            if (strncmp (keyID, "0x", 2) == 0)
+              keyID += 2;
+            goto bypass_selection;		/* you don't see this. */
+          }
+
+          /* check for e-mail address */
+          if (strchr (keyID, '@') &&
+              (addr = rfc822_parse_adrlist (NULL, keyID)))
+          {
+            if (fqdn) rfc822_qualify (addr, fqdn);
+            q = addr;
+          }
+          else if (! oppenc_mode)
+          {
+            k_info = pgp_getkeybystr (keyID, KEYFLAG_CANENCRYPT, PGP_PUBRING);
+          }
+        }
+        else if (r == M_NO)
+        {
+          if (key_selected || (crypt_hook->next != NULL))
+          {
+            crypt_hook = crypt_hook->next;
+            continue;
+          }
+        }
+        else if (r == -1)
+        {
+          FREE (&keylist);
+          rfc822_free_address (&addr);
+          mutt_free_list (&crypt_hook_list);
+          return NULL;
 	}
-	else
-	  k_info = pgp_getkeybystr (keyID, KEYFLAG_CANENCRYPT, PGP_PUBRING);
       }
-      else if (r == -1)
+
+      if (k_info == NULL)
       {
-	FREE (&keylist);
-	rfc822_free_address (&tmp);
-	rfc822_free_address (&addr);
-	return NULL;
+        pgp_invoke_getkeys (q);
+        k_info = pgp_getkeybyaddr (q, KEYFLAG_CANENCRYPT, PGP_PUBRING, oppenc_mode);
       }
-    }
-
-    if (k_info == NULL)
-      pgp_invoke_getkeys (q);
 
-    if (k_info == NULL && (k_info = pgp_getkeybyaddr (q, KEYFLAG_CANENCRYPT, PGP_PUBRING)) == NULL)
-    {
-      snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);
+      if ((k_info == NULL) && (! oppenc_mode))
+      {
+        snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);
+        k_info = pgp_ask_for_key (buf, q->mailbox,
+                              KEYFLAG_CANENCRYPT, PGP_PUBRING);
+      }
 
-      if ((key = pgp_ask_for_key (buf, q->mailbox,
-				  KEYFLAG_CANENCRYPT, PGP_PUBRING)) == NULL)
+      if (k_info == NULL)
       {
 	FREE (&keylist);
-	rfc822_free_address (&tmp);
 	rfc822_free_address (&addr);
+        mutt_free_list (&crypt_hook_list);
 	return NULL;
       }
-    }
-    else
-      key = k_info;
 
-    keyID = pgp_keyid (key);
-    
-  bypass_selection:
-    keylist_size += mutt_strlen (keyID) + 4;
-    safe_realloc (&keylist, keylist_size);
-    sprintf (keylist + keylist_used, "%s0x%s", keylist_used ? " " : "",	/* __SPRINTF_CHECKED__ */
-	     keyID);
-    keylist_used = mutt_strlen (keylist);
+      keyID = pgp_fpr_or_lkeyid (k_info);
+
+    bypass_selection:
+      keylist_size += mutt_strlen (keyID) + 4;
+      safe_realloc (&keylist, keylist_size);
+      sprintf (keylist + keylist_used, "%s0x%s", keylist_used ? " " : "",	/* __SPRINTF_CHECKED__ */
+              keyID);
+      keylist_used = mutt_strlen (keylist);
+
+      key_selected = 1;
 
-    pgp_free_key (&key);
-    rfc822_free_address (&addr);
+      pgp_free_key (&k_info);
+      rfc822_free_address (&addr);
 
+      if (crypt_hook != NULL)
+        crypt_hook = crypt_hook->next;
+
+    } while (crypt_hook != NULL);
+
+    mutt_free_list (&crypt_hook_list);
   }
-  rfc822_free_address (&tmp);
   return (keylist);
 }
 
 /* Warning: "a" is no longer freed in this routine, you need
  * to free it later.  This is necessary for $fcc_attach. */
 
