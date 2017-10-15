       case GPGME_VALIDITY_FULL:
       case GPGME_VALIDITY_ULTIMATE:
 	txt = NULL;
 	break;
       }
   if (txt)
-    state_attach_puts (txt, s);
+    state_puts (txt, s);
 }
 
 static void print_smime_keyinfo (const char* msg, gpgme_signature_t sig,
                                  gpgme_key_t key, STATE *s)
 {
-  size_t msglen;
+  int msgwid;
   gpgme_user_id_t uids = NULL;
   int i, aka = 0;
 
-  state_attach_puts (msg, s);
-  state_attach_puts (" ", s);
+  state_puts (msg, s);
+  state_puts (" ", s);
   /* key is NULL when not present in the user's keyring */
   if (key)
   {
     for (uids = key->uids; uids; uids = uids->next)
     {
       if (uids->revoked)
 	continue;
       if (aka)
       {
-        /* TODO: need to account for msg wide characters
-         * and "aka" translation length */
-	msglen = mutt_strlen (msg) - 4;
-	for (i = 0; i < msglen; i++)
-	  state_attach_puts(" ", s);
-	state_attach_puts(_("aka: "), s);
+	msgwid = mutt_strwidth (msg) - mutt_strwidth (_("aka: ")) + 1;
+	if (msgwid < 0)
+	  msgwid = 0;
+	for (i = 0; i < msgwid; i++)
+	  state_puts(" ", s);
+	state_puts(_("aka: "), s);
       }
-      state_attach_puts (uids->uid, s);
-      state_attach_puts ("\n", s);
+      state_puts (uids->uid, s);
+      state_puts ("\n", s);
 
       aka = 1;
     }
   }
   else
   {
-    state_attach_puts (_("KeyID "), s);
-    state_attach_puts (sig->fpr, s);
-    state_attach_puts ("\n", s);
+    state_puts (_("KeyID "), s);
+    state_puts (sig->fpr, s);
+    state_puts ("\n", s);
+  }
+
+  /* timestamp is 0 when verification failed.
+     "Jan 1 1970" is not the created date. */
+  if (sig->timestamp)
+  {
+    msgwid = mutt_strwidth (msg) - mutt_strwidth (_("created: ")) + 1;
+    if (msgwid < 0)
+      msgwid = 0;
+    for (i = 0; i < msgwid; i++)
+      state_puts(" ", s);
+    state_puts (_("created: "), s);
+    print_time (sig->timestamp, s);
+    state_puts ("\n", s);
   }
-
-  msglen = mutt_strlen (msg) - 8;
-  /* TODO: need to account for msg wide characters
-   * and "created" translation length */
-  for (i = 0; i < msglen; i++)
-    state_attach_puts(" ", s);
-  state_attach_puts (_("created: "), s);
-  print_time (sig->timestamp, s);
-  state_attach_puts ("\n", s);  
 }
 
 /* Show information about one signature.  This function is called with
    the context CTX of a successful verification operation and the
    enumerator IDX which should start at 0 and increment for each
    call/signature. 
