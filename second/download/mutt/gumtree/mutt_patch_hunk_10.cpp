     mutt_error _("Error parsing address!");
     return;
   }
 
   adr = mutt_expand_aliases (adr);
 
+  if (mutt_addrlist_to_idna (adr, &err) < 0)
+  {
+    mutt_error (_("Bad IDN: '%s'"), err);
+    FREE (&err);
+    rfc822_free_address (&adr);
+    return;
+  }
+
   buf[0] = 0;
-  rfc822_write_address (buf, sizeof (buf), adr);
+  rfc822_write_address (buf, sizeof (buf), adr, 1);
 
 #define extra_space (15 + 7 + 2)
-  /*
-   * This is the printing width of "...? ([y=yes]/n=no): ?" plus 2
-   * for good measure. This is not ideal. FIXME.
-   */
-  snprintf (prompt, sizeof (prompt) - 4,
+  snprintf (scratch, sizeof (scratch),
            (h ? _("Bounce message to %s") : _("Bounce messages to %s")), buf);
-  mutt_format_string (prompt, sizeof (prompt) - 4,
-		      0, COLS-extra_space, 0, 0,
-		      prompt, sizeof (prompt), 0);
-  strcat (prompt, "...?");	/* __STRCAT_CHECKED__ */
-  if (mutt_yesorno (prompt, 1) != 1)
+
+  if (mutt_strwidth (prompt) > COLS - extra_space)
+  {
+    mutt_format_string (prompt, sizeof (prompt),
+			0, COLS-extra_space, FMT_LEFT, 0,
+			scratch, sizeof (scratch), 0);
+    safe_strcat (prompt, sizeof (prompt), "...?");
+  }
+  else
+    snprintf (prompt, sizeof (prompt), "%s?", scratch);
+
+  if (query_quadoption (OPT_BOUNCE, prompt) != M_YES)
   {
     rfc822_free_address (&adr);
-    CLEARLINE (LINES-1);
+    CLEARLINE (LINES - 1);
+    mutt_message (h ? _("Message not bounced.") : _("Messages not bounced."));
     return;
   }
 
-  mutt_bounce_message (NULL, h, adr);
+  CLEARLINE (LINES - 1);
+  
+  rc = mutt_bounce_message (NULL, h, adr);
   rfc822_free_address (&adr);
-  mutt_message (h ? _("Message bounced.") : _("Messages bounced."));
+  /* If no error, or background, display message. */
+  if ((rc == 0) || (rc == S_BKG))
+    mutt_message (h ? _("Message bounced.") : _("Messages bounced."));
 }
 
 static void pipe_set_flags (int decode, int print, int *cmflags, int *chflags)
 {
   if (decode)
   {
