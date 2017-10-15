 }
 
 /* enter a mutt command */
 void mutt_enter_command (void)
 {
   BUFFER err, token;
-  char buffer[LONG_STRING], errbuf[SHORT_STRING];
+  char buffer[LONG_STRING];
   int r;
 
   buffer[0] = 0;
   if (mutt_get_field (":", buffer, sizeof (buffer), M_COMMAND) != 0 || !buffer[0])
     return;
-  err.data = errbuf;
-  err.dsize = sizeof (errbuf);
-  memset (&token, 0, sizeof (token));
+  mutt_buffer_init (&err);
+  err.dsize = STRING;
+  err.data = safe_malloc(err.dsize);
+  mutt_buffer_init (&token);
   r = mutt_parse_rc_line (buffer, &token, &err);
   FREE (&token.data);
-  if (errbuf[0])
+  if (err.data[0])
   {
     /* since errbuf could potentially contain printf() sequences in it,
        we must call mutt_error() in this fashion so that vsprintf()
        doesn't expect more arguments that we passed */
     if (r == 0)
-      mutt_message ("%s", errbuf);
+      mutt_message ("%s", err.data);
     else
-      mutt_error ("%s", errbuf);
+      mutt_error ("%s", err.data);
   }
+
+  FREE (&err.data);
 }
 
 void mutt_display_address (ENVELOPE *env)
 {
   char *pfx = NULL;
   char buf[SHORT_STRING];
   ADDRESS *adr = NULL;
 
   adr = mutt_get_address (env, &pfx);
 
   if (!adr) return;
-
+  
+  /* 
+   * Note: We don't convert IDNA to local representation this time.
+   * That is intentional, so the user has an opportunity to copy &
+   * paste the on-the-wire form of the address to other, IDN-unable
+   * software. 
+   */
+  
   buf[0] = 0;
-  rfc822_write_address (buf, sizeof (buf), adr);
+  rfc822_write_address (buf, sizeof (buf), adr, 0);
   mutt_message ("%s: %s", pfx, buf);
 }
 
 static void set_copy_flags (HEADER *hdr, int decode, int decrypt, int *cmflags, int *chflags)
 {
   *cmflags = 0;
   *chflags = CH_UPDATE_LEN;
   
-#ifdef HAVE_PGP
-  if (!decode && decrypt && (hdr->pgp & PGPENCRYPT))
+  if (WithCrypto && !decode && decrypt && (hdr->security & ENCRYPT))
   {
-    if (mutt_is_multipart_encrypted(hdr->content))
+    if ((WithCrypto & APPLICATION_PGP)
+        && mutt_is_multipart_encrypted(hdr->content))
     {
       *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
       *cmflags = M_CM_DECODE_PGP;
     }
-    else if (mutt_is_application_pgp(hdr->content) & PGPENCRYPT)
+    else if ((WithCrypto & APPLICATION_PGP)
+              && mutt_is_application_pgp (hdr->content) & ENCRYPT)
       decode = 1;
+    else if ((WithCrypto & APPLICATION_SMIME)
+             && mutt_is_application_smime(hdr->content) & ENCRYPT)
+    {
+      *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
+      *cmflags = M_CM_DECODE_SMIME;
+    }
   }
-#endif
 
   if (decode)
   {
     *chflags = CH_XMIT | CH_MIME | CH_TXTPLAIN;
     *cmflags = M_CM_DECODE | M_CM_CHARCONV;
-  }
 
-  /* respect $weed only if decode doesn't kick in
-   * for decrypt.
-   */
+    if (!decrypt)	/* If decode doesn't kick in for decrypt, */
+    {
+      *chflags |= CH_DECODE;	/* then decode RFC 2047 headers, */
 
-  if (decode && !decrypt && option (OPTWEED))
-  {
-    *chflags |= CH_WEED;
-    *cmflags |= M_CM_WEED;
+      if (option (OPTWEED))
+      {
+	*chflags |= CH_WEED;	/* and respect $weed. */
+	*cmflags |= M_CM_WEED;
+      }
+    }
   }
 }
 
-void _mutt_save_message (HEADER *h, CONTEXT *ctx, int delete, int decode, int decrypt)
+int _mutt_save_message (HEADER *h, CONTEXT *ctx, int delete, int decode, int decrypt)
 {
   int cmflags, chflags;
+  int rc;
   
   set_copy_flags (h, decode, decrypt, &cmflags, &chflags);
 
   if (decode || decrypt)
     mutt_parse_mime_message (Context, h);
 
-  if (mutt_append_message (ctx, Context, h, cmflags, chflags) == 0 && delete)
+  if ((rc = mutt_append_message (ctx, Context, h, cmflags, chflags)) != 0)
+    return rc;
+
+  if (delete)
   {
     mutt_set_flag (Context, h, M_DELETE, 1);
     if (option (OPTDELETEUNTAG))
       mutt_set_flag (Context, h, M_TAG, 0);
   }
+  
+  return 0;
 }
 
 /* returns 0 if the copy/save was successful, or -1 on error/abort */
 int mutt_save_message (HEADER *h, int delete, 
 		       int decode, int decrypt, int *redraw)
 {
   int i, need_buffy_cleanup;
-#ifdef HAVE_PGP
-  int need_passphrase = 0;
-#endif
+  int need_passphrase = 0, app=0;
   char prompt[SHORT_STRING], buf[_POSIX_PATH_MAX];
   CONTEXT ctx;
   struct stat st;
-#ifdef BUFFY_SIZE
-  BUFFY *tmp = NULL;
-#else
-  struct utimbuf ut;
-#endif
 
   *redraw = 0;
 
   
   snprintf (prompt, sizeof (prompt),
 	    decode  ? (delete ? _("Decode-save%s to mailbox") :
