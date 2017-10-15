 }
 
 /* 
  * Implementation of `encrypted_handler'.
  */
 
-/* MIME handler for pgp/mime encrypted messages. */
+/* MIME handler for pgp/mime encrypted messages.
+ * This handler is passed the application/octet-stream directly.
+ * The caller must propagate a->goodsig to its parent.
+ */
 int pgp_gpgme_encrypted_handler (BODY *a, STATE *s)
 {
   char tempfile[_POSIX_PATH_MAX];
   FILE *fpout;
   BODY *tattach;
-  BODY *orig_body = a;
   int is_signed;
   int rc = 0;
   
   dprint (2, (debugfile, "Entering pgp_encrypted handler\n"));
-  a = a->parts;
-  if (!a || a->type != TYPEAPPLICATION || !a->subtype
-      || ascii_strcasecmp ("pgp-encrypted", a->subtype) 
-      || !a->next || a->next->type != TYPEAPPLICATION || !a->next->subtype
-      || ascii_strcasecmp ("octet-stream", a->next->subtype) )
-    {
-      if (s->flags & M_DISPLAY)
-        state_attach_puts (_("[-- Error: malformed PGP/MIME message! --]\n\n"),
-                           s);
-      return -1;
-    }
-
-  /* Move forward to the application/pgp-encrypted body. */
-  a = a->next;
 
   mutt_mktemp (tempfile, sizeof (tempfile));
   if (!(fpout = safe_fopen (tempfile, "w+")))
     {
       if (s->flags & M_DISPLAY)
         state_attach_puts (_("[-- Error: could not create temporary file! "
