       q = p;
       k_info = NULL;
 
       if (crypt_hook != NULL)
       {
         keyID = crypt_hook->data;
-        r = M_YES;
+        r = MUTT_YES;
         if (! oppenc_mode && option(OPTCRYPTCONFIRMHOOK))
         {
           snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
-          r = mutt_yesorno (buf, M_YES);
+          r = mutt_yesorno (buf, MUTT_YES);
         }
-        if (r == M_YES)
+        if (r == MUTT_YES)
         {
           if (crypt_is_numerical_keyid (keyID))
           {
             if (strncmp (keyID, "0x", 2) == 0)
               keyID += 2;
             goto bypass_selection;		/* you don't see this. */
