 			  (chflags & CH_PREFIX) ? prefix : NULL) == -1)
       return -1;
 
     new_offset = ftello (fpout);
   }
 
-  if (flags & M_CM_DECODE)
+  if (flags & MUTT_CM_DECODE)
   {
     /* now make a text/plain version of the message */
     memset (&s, 0, sizeof (STATE));
     s.fpin = fpin;
     s.fpout = fpout;
-    if (flags & M_CM_PREFIX)
+    if (flags & MUTT_CM_PREFIX)
       s.prefix = prefix;
-    if (flags & M_CM_DISPLAY)
-      s.flags |= M_DISPLAY;
-    if (flags & M_CM_PRINTING)
-      s.flags |= M_PRINTING;
-    if (flags & M_CM_WEED)
-      s.flags |= M_WEED;
-    if (flags & M_CM_CHARCONV)
-      s.flags |= M_CHARCONV;
-    if (flags & M_CM_REPLYING)
-      s.flags |= M_REPLYING;
+    if (flags & MUTT_CM_DISPLAY)
+      s.flags |= MUTT_DISPLAY;
+    if (flags & MUTT_CM_PRINTING)
+      s.flags |= MUTT_PRINTING;
+    if (flags & MUTT_CM_WEED)
+      s.flags |= MUTT_WEED;
+    if (flags & MUTT_CM_CHARCONV)
+      s.flags |= MUTT_CHARCONV;
+    if (flags & MUTT_CM_REPLYING)
+      s.flags |= MUTT_REPLYING;
     
-    if (WithCrypto && flags & M_CM_VERIFY)
-      s.flags |= M_VERIFY;
+    if (WithCrypto && flags & MUTT_CM_VERIFY)
+      s.flags |= MUTT_VERIFY;
 
     rc = mutt_body_handler (body, &s);
   }
   else if (WithCrypto
-           && (flags & M_CM_DECODE_CRYPT) && (hdr->security & ENCRYPT))
+           && (flags & MUTT_CM_DECODE_CRYPT) && (hdr->security & ENCRYPT))
   {
     BODY *cur = NULL;
     FILE *fp;
 
     if ((WithCrypto & APPLICATION_PGP)
-        && (flags & M_CM_DECODE_PGP) && (hdr->security & APPLICATION_PGP) &&
+        && (flags & MUTT_CM_DECODE_PGP) && (hdr->security & APPLICATION_PGP) &&
 	hdr->content->type == TYPEMULTIPART)
     {
       if (crypt_pgp_decrypt_mime (fpin, &fp, hdr->content, &cur))
 	return (-1);
       fputs ("MIME-Version: 1.0\n", fpout);
     }
 
     if ((WithCrypto & APPLICATION_SMIME)
-        && (flags & M_CM_DECODE_SMIME) && (hdr->security & APPLICATION_SMIME)
+        && (flags & MUTT_CM_DECODE_SMIME) && (hdr->security & APPLICATION_SMIME)
 	     && hdr->content->type == TYPEAPPLICATION)
     {
       if (crypt_smime_decrypt_mime (fpin, &fp, hdr->content, &cur))
 	return (-1);
     }
 
