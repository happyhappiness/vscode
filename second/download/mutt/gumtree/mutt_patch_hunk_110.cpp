 
   rfc822_free_address (&env->mail_followup_to);
 
   /* back conversions */
   rfc2047_decode_adrlist (env->to);
   rfc2047_decode_adrlist (env->cc);
+  rfc2047_decode_adrlist (env->bcc);
   rfc2047_decode_adrlist (env->from);
   rfc2047_decode_adrlist (env->reply_to);
   rfc2047_decode (&env->subject);
+  rfc2047_decode (&env->x_label);
 }
 
-static void _mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to, const char *resent_from,
+static int _mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to, const char *resent_from,
 				  ADDRESS *env_from)
 {
-  int i;
+  int i, ret = 0;
   FILE *f;
   char date[SHORT_STRING], tempfile[_POSIX_PATH_MAX];
   MESSAGE *msg = NULL;
 
   if (!h)
   {
+	  /* Try to bounce each message out, aborting if we get any failures. */
     for (i=0; i<Context->msgcount; i++)
       if (Context->hdrs[i]->tagged)
-	_mutt_bounce_message (fp, Context->hdrs[i], to, resent_from, env_from);
-    return;
+        ret |= _mutt_bounce_message (fp, Context->hdrs[i], to, resent_from, env_from);
+    return ret;
   }
 
+  /* If we failed to open a message, return with error */
   if (!fp && (msg = mx_open_message (Context, h->msgno)) == NULL)
-    return;
+    return -1;
 
   if (!fp) fp = msg->fp;
 
-  mutt_mktemp (tempfile);
+  mutt_mktemp (tempfile, sizeof (tempfile));
   if ((f = safe_fopen (tempfile, "w")) != NULL)
   {
-    int ch_flags = CH_XMIT | CH_NONEWLINE;
-    
+    int ch_flags = CH_XMIT | CH_NONEWLINE | CH_NOQFROM;
+    char* msgid_str;
+
     if (!option (OPTBOUNCEDELIVERED))
       ch_flags |= CH_WEED_DELIVERED;
-    
-    fseek (fp, h->offset, 0);
-    mutt_copy_header (fp, h, f, ch_flags, NULL);
+
+    fseeko (fp, h->offset, 0);
     fprintf (f, "Resent-From: %s", resent_from);
     fprintf (f, "\nResent-%s", mutt_make_date (date, sizeof(date)));
+    msgid_str = mutt_gen_msgid();
+    fprintf (f, "Resent-Message-ID: %s\n", msgid_str);
     fputs ("Resent-To: ", f);
-    mutt_write_address_list (to, f, 11);
+    mutt_write_address_list (to, f, 11, 0);
+    mutt_copy_header (fp, h, f, ch_flags, NULL);
     fputc ('\n', f);
     mutt_copy_bytes (fp, f, h->content->length);
-    fclose (f);
+    safe_fclose (&f);
+    FREE (&msgid_str);
 
-    mutt_invoke_sendmail (env_from, to, NULL, NULL, tempfile,
-			  h->content->encoding == ENC8BIT);
+#if USE_SMTP
+    if (SmtpUrl)
+      ret = mutt_smtp_send (env_from, to, NULL, NULL, tempfile,
+                            h->content->encoding == ENC8BIT);
+    else
+#endif /* USE_SMTP */
+    ret = mutt_invoke_sendmail (env_from, to, NULL, NULL, tempfile,
+			  	h->content->encoding == ENC8BIT);
   }
 
   if (msg)
     mx_close_message (&msg);
+
+  return ret;
 }
 
-void mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to)
+int mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to)
 {
-  ADDRESS *from;
+  ADDRESS *from, *resent_to;
   const char *fqdn = mutt_fqdn (1);
   char resent_from[STRING];
+  int ret;
+  char *err;
 
   resent_from[0] = '\0';
   from = mutt_default_from ();
 
+  /*
+   * mutt_default_from() does not use $realname if the real name is not set
+   * in $from, so we add it here.  The reason it is not added in
+   * mutt_default_from() is that during normal sending, we execute
+   * send-hooks and set the realname last so that it can be changed based
+   * upon message criteria.
+   */
+  if (! from->personal)
+    from->personal = safe_strdup(Realname);
+
   if (fqdn)
     rfc822_qualify (from, fqdn);
 
   rfc2047_encode_adrlist (from, "Resent-From");
-  
-  rfc822_write_address (resent_from, sizeof (resent_from), from);
+  if (mutt_addrlist_to_idna (from, &err))
+  {
+    mutt_error (_("Bad IDN %s while preparing resent-from."),
+		err);
+    rfc822_free_address (&from);
+    return -1;
+  }
+  rfc822_write_address (resent_from, sizeof (resent_from), from, 0);
+
+  /*
+   * prepare recipient list. idna conversion appears to happen before this
+   * function is called, since the user receives confirmation of the address
+   * list being bounced to.
+   */
+  resent_to = rfc822_cpy_adr(to, 0);
+  rfc2047_encode_adrlist(resent_to, "Resent-To");
 
-  _mutt_bounce_message (fp, h, to, resent_from, from);
+  ret = _mutt_bounce_message (fp, h, resent_to, resent_from, from);
 
+  rfc822_free_address (&resent_to);
   rfc822_free_address (&from);
+
+  return ret;
 }
 
 
 /* given a list of addresses, return a list of unique addresses */
 ADDRESS *mutt_remove_duplicates (ADDRESS *addr)
 {
-  ADDRESS *top = NULL;
+  ADDRESS *top = addr;
+  ADDRESS **last = &top;
   ADDRESS *tmp;
-  
-  if ((top = addr) == NULL)
-    return (NULL);
-  addr = addr->next;
-  top->next = NULL;
+  int dup;
+
   while (addr)
   {
-    tmp = top;
-    do {
-      if (addr->mailbox && tmp->mailbox &&
+    for (tmp = top, dup = 0; tmp && tmp != addr; tmp = tmp->next)
+    {
+      if (tmp->mailbox && addr->mailbox &&
 	  !ascii_strcasecmp (addr->mailbox, tmp->mailbox))
       {
-	/* duplicate address, just ignore it */
-	tmp = addr;
-	addr = addr->next;
-	tmp->next = NULL;
-	rfc822_free_address (&tmp);
-      }
-      else if (!tmp->next)
-      {
-	/* unique address.  add it to the list */
-	tmp->next = addr;
-	addr = addr->next;
-	tmp = tmp->next;
-	tmp->next = NULL;
-	tmp = NULL; /* so we exit the loop */
+	dup = 1;
+	break;
       }
-      else
-	tmp = tmp->next;
-    } while (tmp);
+    }
+
+    if (dup)
+    {
+      dprint (2, (debugfile, "mutt_remove_duplicates: Removing %s\n",
+		  addr->mailbox));
+
+      *last = addr->next;
+
+      addr->next = NULL;
+      rfc822_free_address(&addr);
+
+      addr = *last;
+    }
+    else
+    {
+      last = &addr->next;
+      addr = addr->next;
+    }
   }
 
   return (top);
 }
 
 static void set_noconv_flags (BODY *b, short flag)
