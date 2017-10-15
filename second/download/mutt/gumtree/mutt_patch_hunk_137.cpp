 
 int pgp_decrypt_mime (FILE *fpin, FILE **fpout, BODY *b, BODY **cur)
 {
   char tempfile[_POSIX_PATH_MAX];
   STATE s;
   BODY *p = b;
-  
-  if(!mutt_is_multipart_encrypted(b))
-    return -1;
+  int need_decode = 0;
+  int saved_type;
+  LOFF_T saved_offset;
+  size_t saved_length;
+  FILE *decoded_fp = NULL;
+  int rv = 0;
 
-  if(!b->parts || !b->parts->next)
+  if (mutt_is_valid_multipart_pgp_encrypted (b))
+    b = b->parts->next;
+  else if (mutt_is_malformed_multipart_pgp_encrypted (b))
+  {
+    b = b->parts->next->next;
+    need_decode = 1;
+  }
+  else
     return -1;
-  
-  b = b->parts->next;
-  
+
   memset (&s, 0, sizeof (s));
   s.fpin = fpin;
+
+  if (need_decode)
+  {
+    saved_type = b->type;
+    saved_offset = b->offset;
+    saved_length = b->length;
+
+    mutt_mktemp (tempfile, sizeof (tempfile));
+    if ((decoded_fp = safe_fopen (tempfile, "w+")) == NULL)
+    {
+      mutt_perror (tempfile);
+      return (-1);
+    }
+    unlink (tempfile);
+
+    fseeko (s.fpin, b->offset, 0);
+    s.fpout = decoded_fp;
+
+    mutt_decode_attachment (b, &s);
+
+    fflush (decoded_fp);
+    b->length = ftello (decoded_fp);
+    b->offset = 0;
+    rewind (decoded_fp);
+    s.fpin = decoded_fp;
+    s.fpout = 0;
+  }
+
   mutt_mktemp (tempfile, sizeof (tempfile));
   if ((*fpout = safe_fopen (tempfile, "w+")) == NULL)
   {
     mutt_perror (tempfile);
-    return (-1);
+    rv = -1;
+    goto bail;
   }
   unlink (tempfile);
 
-  *cur = pgp_decrypt_part (b, &s, *fpout, p);
-
+  if ((*cur = pgp_decrypt_part (b, &s, *fpout, p)) == NULL)
+    rv = -1;
   rewind (*fpout);
-  
-  if (!*cur)
-    return -1;
-  
-  return (0);
+
+bail:
+  if (need_decode)
+  {
+    b->type = saved_type;
+    b->length = saved_length;
+    b->offset = saved_offset;
+    safe_fclose (&decoded_fp);
+  }
+
+  return rv;
 }
 
+/*
+ * This handler is passed the application/octet-stream directly.
+ * The caller must propagate a->goodsig to its parent.
+ */
 int pgp_encrypted_handler (BODY *a, STATE *s)
 {
   char tempfile[_POSIX_PATH_MAX];
   FILE *fpout, *fpin;
   BODY *tattach;
-  BODY *p = a;
   int rc = 0;
-  
-  a = a->parts;
-  if (!a || a->type != TYPEAPPLICATION || !a->subtype || 
-      ascii_strcasecmp ("pgp-encrypted", a->subtype) != 0 ||
-      !a->next || a->next->type != TYPEAPPLICATION || !a->next->subtype ||
-      ascii_strcasecmp ("octet-stream", a->next->subtype) != 0)
-  {
-    if (s->flags & M_DISPLAY)
-      state_attach_puts (_("[-- Error: malformed PGP/MIME message! --]\n\n"), s);
-    return -1;
-  }
-
-  /*
-   * Move forward to the application/pgp-encrypted body.
-   */
-  a = a->next;
 
   mutt_mktemp (tempfile, sizeof (tempfile));
   if ((fpout = safe_fopen (tempfile, "w+")) == NULL)
   {
     if (s->flags & M_DISPLAY)
       state_attach_puts (_("[-- Error: could not create temporary file! --]\n"), s);
     return -1;
   }
 
   if (s->flags & M_DISPLAY) crypt_current_time (s, "PGP");
 
-  if ((tattach = pgp_decrypt_part (a, s, fpout, p)) != NULL)
+  if ((tattach = pgp_decrypt_part (a, s, fpout, a)) != NULL)
   {
     if (s->flags & M_DISPLAY)
       state_attach_puts (_("[-- The following data is PGP/MIME encrypted --]\n\n"), s);
 
     fpin = s->fpin;
     s->fpin = fpout;
