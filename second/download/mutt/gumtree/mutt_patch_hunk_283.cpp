   char shortbuf[SHORT_STRING];
   unsigned long aval = 0;
   const char *delim;
   int is_pgp = 0;
   int i;
   gpgme_user_id_t uid = NULL;
+  static int max_header_width = 0;
+  int width;
+
+  if (!max_header_width)
+  {
+    for (i = 0; i < KIP_END; i++)
+    {
+      KeyInfoPadding[i] = mutt_strlen (_(KeyInfoPrompts[i]));
+      width = mutt_strwidth (_(KeyInfoPrompts[i]));
+      if (max_header_width < width)
+        max_header_width = width;
+      KeyInfoPadding[i] -= width;
+    }
+    for (i = 0; i < KIP_END; i++)
+      KeyInfoPadding[i] += max_header_width;
+  }
 
   is_pgp = key->protocol == GPGME_PROTOCOL_OpenPGP;
 
   for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
     {
       if (uid->revoked)
         continue;
 
       s = uid->uid;
-      /* L10N:
-         Fill dots to make the DOTFILL entries the same length.
-         In English, msgid "Fingerprint: " is the longest entry for this menu.
-         Your language may vary. */
-      fputs (idx ? _(" aka ......: ") :_("Name ......: "), fp);
+
+      if (!idx)
+        fprintf (fp, "%*s", KeyInfoPadding[KIP_NAME], _(KeyInfoPrompts[KIP_NAME]));
+      else
+        fprintf (fp, "%*s", KeyInfoPadding[KIP_AKA], _(KeyInfoPrompts[KIP_AKA]));
       if (uid->invalid)
         {
+          /* L10N: comes after the Name or aka if the key is invalid */
           fputs (_("[Invalid]"), fp);
           putc (' ', fp);
         }
       if (is_pgp)
         print_utf8 (fp, s, strlen(s));
       else
