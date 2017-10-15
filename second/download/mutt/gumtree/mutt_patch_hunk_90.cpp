   t->parts->next = mutt_new_body ();
   t->parts->next->type = TYPEAPPLICATION;
   t->parts->next->subtype = safe_strdup ("octet-stream");
   t->parts->next->encoding = ENC7BIT;
   t->parts->next->filename = safe_strdup (tempfile);
   t->parts->next->use_disp = 1;
-  t->parts->next->disposition = DISPINLINE;
+  t->parts->next->disposition = DISPATTACH;
   t->parts->next->unlink = 1; /* delete after sending the message */
   t->parts->next->d_filename = safe_strdup ("msg.asc"); /* non pgp/mime can save */
 
   return (t);
 }
 
-static BODY *pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
+BODY *pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
 {
   BODY *b;
 
   char pgpoutfile[_POSIX_PATH_MAX];
   char pgperrfile[_POSIX_PATH_MAX];
   char pgpinfile[_POSIX_PATH_MAX];
   
+  char body_charset[STRING];
+  char *from_charset;
+  const char *send_charset;
+  
   FILE *pgpout = NULL, *pgperr = NULL, *pgpin = NULL;
   FILE *fp;
 
-  int empty;
+  int empty = 0;
   int err;
 
   char buff[STRING];
 
   pid_t thepid;
+
+  if (a->type != TYPETEXT)
+    return NULL;
+  if (ascii_strcasecmp (a->subtype, "plain"))
+    return NULL;
   
   if ((fp = fopen (a->filename, "r")) == NULL)
   {
     mutt_perror (a->filename);
     return NULL;
   }
   
-  mutt_mktemp (pgpinfile);
+  mutt_mktemp (pgpinfile, sizeof (pgpinfile));
   if ((pgpin = safe_fopen (pgpinfile, "w")) == NULL)
   {
     mutt_perror (pgpinfile);
-    fclose (fp);
+    safe_fclose (&fp);
     return NULL;
   }
 
-  mutt_copy_stream (fp, pgpin);
-  fclose (fp);
-  fclose (pgpin);
+  /* The following code is really correct:  If noconv is set,
+   * a's charset parameter contains the on-disk character set, and
+   * we have to convert from that to utf-8.  If noconv is not set,
+   * we have to convert from $charset to utf-8.
+   */
+  
+  mutt_get_body_charset (body_charset, sizeof (body_charset), a);
+  if (a->noconv)
+    from_charset = body_charset;
+  else 
+    from_charset = Charset;
+    
+  if (!mutt_is_us_ascii (body_charset))
+  {
+    int c;
+    FGETCONV *fc;
+    
+    if (flags & ENCRYPT)
+      send_charset = "us-ascii";
+    else
+      send_charset = "utf-8";
+
+    /* fromcode is assumed to be correct: we set flags to 0 */
+    fc = fgetconv_open (fp, from_charset, "utf-8", 0);
+    while ((c = fgetconv (fc)) != EOF)
+      fputc (c, pgpin);
+    
+    fgetconv_close (&fc);
+  }
+  else
+  {
+    send_charset = "us-ascii";
+    mutt_copy_stream (fp, pgpin);
+  }
+  safe_fclose (&fp);
+  safe_fclose (&pgpin);
 
-  mutt_mktemp (pgpoutfile);
-  mutt_mktemp (pgperrfile);
+  mutt_mktemp (pgpoutfile, sizeof (pgpoutfile));
+  mutt_mktemp (pgperrfile, sizeof (pgperrfile));
   if ((pgpout = safe_fopen (pgpoutfile, "w+")) == NULL ||
       (pgperr = safe_fopen (pgperrfile, "w+")) == NULL)
   {
     mutt_perror (pgpout ? pgperrfile : pgpoutfile);
     unlink (pgpinfile);
     if (pgpout) 
     {
-      fclose (pgpout);
+      safe_fclose (&pgpout);
       unlink (pgpoutfile);
     }
     return NULL;
   }
   
   unlink (pgperrfile);
-  
+
   if ((thepid = pgp_invoke_traditional (&pgpin, NULL, NULL, 
 					-1, fileno (pgpout), fileno (pgperr),
 					pgpinfile, keylist, flags)) == -1)
   {
     mutt_perror _("Can't invoke PGP");
-    fclose (pgpout);
-    fclose (pgperr);
+    safe_fclose (&pgpout);
+    safe_fclose (&pgperr);
     mutt_unlink (pgpinfile);
     unlink (pgpoutfile);
     return NULL;
   }
 
-  if (flags & PGPSIGN)
+  if (pgp_use_gpg_agent())
+    *PgpPass = 0;
+  if (flags & SIGN)
     fprintf (pgpin, "%s\n", PgpPass);
-  fclose (pgpin);
+  safe_fclose (&pgpin);
 
-  mutt_wait_filter (thepid);
+  if(mutt_wait_filter (thepid) && option(OPTPGPCHECKEXIT))
+    empty=1;
 
   mutt_unlink (pgpinfile);
 
   fflush (pgpout);
   fflush (pgperr);
 
   rewind (pgpout);
   rewind (pgperr);
   
-  empty = (fgetc (pgpout) == EOF);
-  fclose (pgpout);
+  if(!empty)
+    empty = (fgetc (pgpout) == EOF);
+  safe_fclose (&pgpout);
   
   err = 0;
   
   while (fgets (buff, sizeof (buff), pgperr))
   {
     err = 1;
     fputs (buff, stdout);
   }
   
-  fclose (pgperr);
+  safe_fclose (&pgperr);
   
   if (err)
     mutt_any_key_to_continue (NULL);
   
   if (empty)
   {
+    if (flags & SIGN)
+      pgp_void_passphrase (); /* just in case */
     unlink (pgpoutfile);
     return NULL;
   }
     
   b = mutt_new_body ();
   
   b->encoding = ENC7BIT;
 
-  b->type = TYPEAPPLICATION;
-  b->subtype = safe_strdup ("pgp");
-
-  mutt_set_parameter ("format", "text", &b->parameter);
-  mutt_set_parameter ("x-action", flags & PGPENCRYPT ? "encrypt" : "sign",
+  b->type = TYPETEXT;
+  b->subtype = safe_strdup ("plain");
+  
+  mutt_set_parameter ("x-action", flags & ENCRYPT ? "pgp-encrypted" : "pgp-signed",
 		      &b->parameter);
-
+  mutt_set_parameter ("charset", send_charset, &b->parameter);
+  
   b->filename = safe_strdup (pgpoutfile);
   
+#if 0
   /* The following is intended to give a clue to some completely brain-dead 
    * "mail environments" which are typically used by large corporations.
    */
 
   b->d_filename = safe_strdup ("msg.pgp");
-  b->disposition = DISPINLINE;
-  b->unlink   = 1;
   b->use_disp = 1;
 
-  return b;
-}
-
-
-
-int pgp_get_keys (HEADER *msg, char **pgpkeylist)
-{
-  /* Do a quick check to make sure that we can find all of the encryption
-   * keys if the user has requested this service.
-   */
-
-  set_option (OPTPGPCHECKTRUST);
+#endif
 
-  *pgpkeylist = NULL;
-  if (msg->pgp & PGPENCRYPT)
-  {
-    if ((*pgpkeylist = pgp_findKeys (msg->env->to, msg->env->cc,
-				      msg->env->bcc)) == NULL)
-      return (-1);
-  }
+  b->disposition = DISPNONE;
+  b->unlink   = 1;
 
-  return (0);
+  b->noconv = 1;
+  b->use_disp = 0;
+  
+  if (!(flags & ENCRYPT))
+    b->encoding = a->encoding;
+  
+  return b;
 }
 
-int pgp_protect (HEADER *msg, char *pgpkeylist)
+int pgp_send_menu (HEADER *msg, int *redraw)
 {
-  BODY *pbody = NULL;
-  int flags = msg->pgp;
-  int traditional = 0;
-  int i;
-
-  if ((msg->pgp & PGPSIGN) && !pgp_valid_passphrase ())
-    return (-1);
+  int choice;
+  
+  if (!(WithCrypto & APPLICATION_PGP))
+    return msg->security;
 
-  if ((msg->content->type == TYPETEXT) &&
-      !ascii_strcasecmp (msg->content->subtype, "plain") &&
-      ((flags & PGPENCRYPT) || (msg->content->content && msg->content->content->hibin == 0)))
+  /* If autoinline and no crypto options set, then set inline. */
+  if (option (OPTPGPAUTOINLINE) && 
+      !((msg->security & APPLICATION_PGP) && (msg->security & (SIGN|ENCRYPT))))
+    msg->security |= INLINE;
+  
+  /* When the message is not selected for signing or encryption, the toggle
+   * between PGP/MIME and Traditional doesn't make sense.
+   */
+  if (msg->security & (ENCRYPT | SIGN))
   {
-    if ((i = query_quadoption (OPT_PGPTRADITIONAL, _("Create an application/pgp message?"))) == -1)
-      return -1;
-    else if (i == M_YES)
-      traditional = 1;
-  }
+    char prompt[LONG_STRING];
 
-  mutt_message _("Invoking PGP...");
+    snprintf (prompt, sizeof (prompt), 
+	_("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, %s format, or (c)lear? "),
+	(msg->security & INLINE) ? _("PGP/M(i)ME") : _("(i)nline"));
 
-  if (!isendwin ())
-    mutt_endwin (NULL);
-
-  if (traditional)
+    /* The keys accepted for this prompt *must* match the order in the second
+     * version in the else clause since the switch statement below depends on
+     * it.  The 'i' key is appended in this version.
+     */
+    choice = mutt_multi_choice (prompt, _("esabfci"));
+  }
+  else
   {
-    if (!(pbody = pgp_traditional_encryptsign (msg->content, flags, pgpkeylist)))
-      return -1;
-    
-    msg->content = pbody;
-    return 0;
+    /* The keys accepted *must* be a prefix of the accepted keys in the "if"
+     * clause above since the switch statement below depends on it.
+     */
+    choice = mutt_multi_choice(_("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, or (c)lear? "),
+	_("esabfc"));
   }
 
-  if ((flags & PGPSIGN) && (!(flags & PGPENCRYPT) || option (OPTPGPRETAINABLESIG)))
+  switch (choice)
   {
-    if (!(pbody = pgp_sign_message (msg->content)))
-      return -1;
+    case 1: /* (e)ncrypt */
+      msg->security |= ENCRYPT;
+      msg->security &= ~SIGN;
+      break;
 
-    msg->content = pbody;
-    flags &= ~PGPSIGN;
-  }
+  case 2: /* (s)ign */
+    msg->security |= SIGN;
+    msg->security &= ~ENCRYPT;
+    break;
 
-  if (flags & PGPENCRYPT)
-  {
-    if (!(pbody = pgp_encrypt_message (msg->content, pgpkeylist, flags & PGPSIGN)))
+  case 3: /* sign (a)s */
     {
+      pgp_key_t p;
+      char input_signas[SHORT_STRING];
+
+      unset_option(OPTPGPCHECKTRUST);
+
+      if ((p = pgp_ask_for_key (_("Sign as: "), NULL, 0, PGP_SECRING)))
+      {
+	snprintf (input_signas, sizeof (input_signas), "0x%s",
+	    pgp_keyid (p));
+	mutt_str_replace (&PgpSignAs, input_signas);
+	pgp_free_key (&p);
+
+	msg->security |= SIGN;
 
-      /* did we perform a retainable signature? */
-      if (flags != msg->pgp)
+	crypt_pgp_void_passphrase ();  /* probably need a different passphrase */
+      }
+#if 0
+      else
       {
-	/* remove the outer multipart layer */
-	msg->content = mutt_remove_multipart (msg->content);
-	/* get rid of the signature */
-	mutt_free_body (&msg->content->next);
+	msg->security &= ~SIGN;
       }
+#endif
 
-      return (-1);
-    }
+      *redraw = REDRAW_FULL;
+    } break;
 
-    /* destroy temporary signature envelope when doing retainable 
-     * signatures.
-     */
-    if (flags != msg->pgp)
-    {
-      mutt_remove_multipart (msg->content);
-      mutt_free_body (&msg->content->next);
-    }
-    
-    msg->content = pbody;
+  case 4: /* (b)oth */
+    msg->security |= (ENCRYPT | SIGN);
+    break;
+
+  case 5: /* (f)orget it */
+  case 6: /* (c)lear     */
+    msg->security = 0;
+    break;
+
+  case 7: /* toggle (i)nline */
+    msg->security ^= INLINE;
+    break;
   }
 
-  return (0);
+  if (msg->security)
+  {
+    if (! (msg->security & (ENCRYPT | SIGN)))
+      msg->security = 0;
+    else
+      msg->security |= APPLICATION_PGP;
+  }
+
+  return (msg->security);
 }
 
-#endif /* HAVE_PGP */
+
+#endif /* CRYPT_BACKEND_CLASSIC_PGP */
