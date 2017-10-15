 int mutt_write_fcc (const char *path, HEADER *hdr, const char *msgid, int post, char *fcc)
 {
   CONTEXT f;
   MESSAGE *msg;
   char tempfile[_POSIX_PATH_MAX];
   FILE *tempfp = NULL;
-  int r;
+  int r, need_buffy_cleanup = 0;
+  struct stat st;
+  char buf[SHORT_STRING];
 
   if (post)
     set_noconv_flags (hdr->content, 1);
-  
+
   if (mx_open_mailbox (path, M_APPEND | M_QUIET, &f) == NULL)
   {
     dprint (1, (debugfile, "mutt_write_fcc(): unable to open mailbox %s in append-mode, aborting.\n",
 		path));
     return (-1);
   }
 
   /* We need to add a Content-Length field to avoid problems where a line in
-   * the message body begins with "From "   
+   * the message body begins with "From "
    */
-  if (f.magic == M_MMDF || f.magic == M_MBOX || f.magic == M_KENDRA)
+  if (f.magic == M_MMDF || f.magic == M_MBOX)
   {
-    mutt_mktemp (tempfile);
+    mutt_mktemp (tempfile, sizeof (tempfile));
     if ((tempfp = safe_fopen (tempfile, "w+")) == NULL)
     {
       mutt_perror (tempfile);
       mx_close_mailbox (&f, NULL);
       return (-1);
     }
+    /* remember new mail status before appending message */
+    need_buffy_cleanup = 1;
+    stat (path, &st);
   }
 
   hdr->read = !post; /* make sure to put it in the `cur' directory (maildir) */
   if ((msg = mx_open_new_message (&f, hdr, M_ADD_FROM)) == NULL)
   {
     mx_close_mailbox (&f, NULL);
     return (-1);
   }
 
   /* post == 1 => postpone message. Set mode = -1 in mutt_write_rfc822_header()
-   * post == 0 => Normal mode. Set mode = 0 in mutt_write_rfc822_header() 
+   * post == 0 => Normal mode. Set mode = 0 in mutt_write_rfc822_header()
    * */
   mutt_write_rfc822_header (msg->fp, hdr->env, hdr->content, post ? -post : 0, 0);
 
   /* (postponment) if this was a reply of some sort, <msgid> contians the
    * Message-ID: of message replied to.  Save it using a special X-Mutt-
    * header so it can be picked up if the message is recalled at a later
    * point in time.  This will allow the message to be marked as replied if
    * the same mailbox is still open.
    */
   if (post && msgid)
     fprintf (msg->fp, "X-Mutt-References: %s\n", msgid);
-  
+
   /* (postponment) save the Fcc: using a special X-Mutt- header so that
-   * it can be picked up when the message is recalled 
+   * it can be picked up when the message is recalled
    */
   if (post && fcc)
     fprintf (msg->fp, "X-Mutt-Fcc: %s\n", fcc);
-  fprintf (msg->fp, "Status: RO\n");
 
+  if (f.magic == M_MMDF || f.magic == M_MBOX)
+    fprintf (msg->fp, "Status: RO\n");
 
+  /* mutt_write_rfc822_header() only writes out a Date: header with
+   * mode == 0, i.e. _not_ postponment; so write out one ourself */
+  if (post)
+    fprintf (msg->fp, "%s", mutt_make_date (buf, sizeof (buf)));
 
-#ifdef HAVE_PGP
   /* (postponment) if the mail is to be signed or encrypted, save this info */
-  if (post && (hdr->pgp & (PGPENCRYPT | PGPSIGN)))
+  if ((WithCrypto & APPLICATION_PGP)
+      && post && (hdr->security & APPLICATION_PGP))
   {
     fputs ("X-Mutt-PGP: ", msg->fp);
-    if (hdr->pgp & PGPENCRYPT) 
+    if (hdr->security & ENCRYPT)
       fputc ('E', msg->fp);
-    if (hdr->pgp & PGPSIGN)
+    if (hdr->security & SIGN)
     {
       fputc ('S', msg->fp);
       if (PgpSignAs && *PgpSignAs)
         fprintf (msg->fp, "<%s>", PgpSignAs);
     }
+    if (hdr->security & INLINE)
+      fputc ('I', msg->fp);
+    fputc ('\n', msg->fp);
+  }
+
+  /* (postponment) if the mail is to be signed or encrypted, save this info */
+  if ((WithCrypto & APPLICATION_SMIME)
+      && post && (hdr->security & APPLICATION_SMIME))
+  {
+    fputs ("X-Mutt-SMIME: ", msg->fp);
+    if (hdr->security & ENCRYPT) {
+	fputc ('E', msg->fp);
+	if (SmimeCryptAlg && *SmimeCryptAlg)
+	    fprintf (msg->fp, "C<%s>", SmimeCryptAlg);
+    }
+    if (hdr->security & SIGN) {
+	fputc ('S', msg->fp);
+	if (SmimeDefaultKey && *SmimeDefaultKey)
+	    fprintf (msg->fp, "<%s>", SmimeDefaultKey);
+    }
+    if (hdr->security & INLINE)
+      fputc ('I', msg->fp);
     fputc ('\n', msg->fp);
   }
-#endif /* HAVE_PGP */
 
 #ifdef MIXMASTER
-  /* (postponement) if the mail is to be sent through a mixmaster 
+  /* (postponement) if the mail is to be sent through a mixmaster
    * chain, save that information
    */
-  
+
   if (post && hdr->chain && hdr->chain)
   {
     LIST *p;
 
     fputs ("X-Mutt-Mix:", msg->fp);
     for (p = hdr->chain; p; p = p->next)
       fprintf (msg->fp, " %s", (char *) p->data);
-    
+
     fputc ('\n', msg->fp);
   }
-#endif    
+#endif
 
   if (tempfp)
   {
     char sasha[LONG_STRING];
     int lines = 0;
 
     mutt_write_mime_body (hdr->content, tempfp);
 
     /* make sure the last line ends with a newline.  Emacs doesn't ensure
-     * this will happen, and it can cause problems parsing the mailbox   
+     * this will happen, and it can cause problems parsing the mailbox
      * later.
      */
     fseek (tempfp, -1, 2);
     if (fgetc (tempfp) != '\n')
     {
       fseek (tempfp, 0, 2);
