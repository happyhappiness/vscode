   {
     adr = iadr;
   }
 
   if (adr && adr->mailbox)
   {
-    strfcpy (buf, adr->mailbox, sizeof (buf));
-    if ((pc = strchr (buf, '@')))
+    strfcpy (tmp, adr->mailbox, sizeof (tmp));
+    if ((pc = strchr (tmp, '@')))
       *pc = 0;
   }
   else
-    buf[0] = '\0';
+    tmp[0] = '\0';
+
+  /* Don't suggest a bad alias name in the event of a strange local part. */
+  mutt_check_alias_name (tmp, buf, sizeof (buf));
   
+retry_name:
   /* add a new alias */
   if (mutt_get_field (_("Alias as: "), buf, sizeof (buf), 0) != 0 || !buf[0])
     return;
 
   /* check to see if the user already has an alias defined */
   if (mutt_lookup_alias (buf))
   {
     mutt_error _("You already have an alias defined with that name!");
     return;
   }
-
+  
+  if (mutt_check_alias_name (buf, fixed, sizeof (fixed)))
+  {
+    switch (mutt_yesorno (_("Warning: This alias name may not work.  Fix it?"), M_YES))
+    {
+      case M_YES:
+      	strfcpy (buf, fixed, sizeof (buf));
+	goto retry_name;
+      case -1: 
+	return;
+    }
+  }
+  
   new       = safe_calloc (1, sizeof (ALIAS));
   new->self = new;
   new->name = safe_strdup (buf);
 
+  mutt_addrlist_to_local (adr);
+  
   if (adr)
     strfcpy (buf, adr->mailbox, sizeof (buf));
   else
     buf[0] = 0;
 
+  mutt_addrlist_to_idna (adr, NULL);
+  
   do
   {
     if (mutt_get_field (_("Address: "), buf, sizeof (buf), 0) != 0 || !buf[0])
     {
       mutt_free_alias (&new);
       return;
     }
     
     if((new->addr = rfc822_parse_adrlist (new->addr, buf)) == NULL)
       BEEP ();
+    if (mutt_addrlist_to_idna (new->addr, &err))
+    {
+      mutt_error (_("Error: '%s' is a bad IDN."), err);
+      mutt_sleep (2);
+      continue;
+    }
   }
   while(new->addr == NULL);
   
   if (adr && adr->personal && !mutt_is_mail_list (adr))
     strfcpy (buf, adr->personal, sizeof (buf));
   else
