   for (idx = 0, uid = key->uids; uid; idx++, uid = uid->next)
     {
       if (uid->revoked)
         continue;
 
       s = uid->uid;
+      /* L10N:
+         Fill dots to make the DOTFILL entries the same length.
+         In English, msgid "Fingerprint: " is the longest entry for this menu.
+         Your language may vary. */
       fputs (idx ? _(" aka ......: ") :_("Name ......: "), fp);
       if (uid->invalid)
         {
           fputs (_("[Invalid]"), fp);
           putc (' ', fp);
         }
