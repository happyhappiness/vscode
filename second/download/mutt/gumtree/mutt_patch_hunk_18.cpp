  	CH_REORDER	output header in order specified by `hdr_order'
   	CH_TXTPLAIN	generate text/plain MIME headers [hack alert.]
  	CH_UPDATE	write new Status: and X-Status:
  	CH_UPDATE_LEN	write new Content-Length: and Lines:
  	CH_XMIT		ignore Lines: and Content-Length:
  	CH_WEED		do header weeding
+	CH_NOQFROM      ignore ">From " line
+	CH_UPDATE_IRT	update the In-Reply-To: header
+	CH_UPDATE_REFS	update the References: header
 
    prefix
    	string to use if CH_PREFIX is set
  */
 
 int
 mutt_copy_header (FILE *in, HEADER *h, FILE *out, int flags, const char *prefix)
 {
   char buffer[SHORT_STRING];
+
+  if (h->env)
+    flags |= (h->env->irt_changed ? CH_UPDATE_IRT : 0)
+      | (h->env->refs_changed ? CH_UPDATE_REFS : 0);
   
   if (mutt_copy_hdr (in, out, h->offset, h->content->offset, flags, prefix) == -1)
-    return (-1);
+    return -1;
 
   if (flags & CH_TXTPLAIN)
   {
     char chsbuf[SHORT_STRING];
-    fputs ("Mime-Version: 1.0\n", out);
+    fputs ("MIME-Version: 1.0\n", out);
     fputs ("Content-Transfer-Encoding: 8bit\n", out);
     fputs ("Content-Type: text/plain; charset=", out);
     mutt_canonical_charset (chsbuf, sizeof (chsbuf), Charset ? Charset : "us-ascii");
     rfc822_cat(buffer, sizeof(buffer), chsbuf, MimeSpecials);
     fputs(buffer, out);
     fputc('\n', out);
-    
-    if (ferror (out) != 0 || feof (out) != 0)
-      return -1;
-    
   }
 
-  if (flags & CH_UPDATE)
+  if ((flags & CH_UPDATE_IRT) && h->env->in_reply_to)
   {
-    if ((flags & CH_NOSTATUS) == 0)
+    LIST *listp = h->env->in_reply_to;
+    fputs ("In-Reply-To:", out);
+    for (; listp; listp = listp->next)
     {
-      if (h->old || h->read)
-      {
-	if (fputs ("Status: ", out) == EOF)
-	  return (-1);
-
-	if (h->read)
-	{
-	  if (fputs ("RO", out) == EOF)
-	    return (-1);
-	}
-	else if (h->old)
-	{
-	  if (fputc ('O', out) == EOF)
-	    return (-1);
-	}
-
-	if (fputc ('\n', out) == EOF)
-	  return (-1);
-      }
+      fputc (' ', out);
+      fputs (listp->data, out);
+    }
+    fputc ('\n', out);
+  }
 
-      if (h->flagged || h->replied)
-      {
-	if (fputs ("X-Status: ", out) == EOF)
-	  return (-1);
+  if ((flags & CH_UPDATE_REFS) && h->env->references)
+  {
+    fputs ("References:", out);
+    mutt_write_references (h->env->references, out, 0);
+    fputc ('\n', out);
+  }
 
-	if (h->replied)
-	{
-	  if (fputc ('A', out) == EOF)
-	    return (-1);
-	}
+  if ((flags & CH_UPDATE) && (flags & CH_NOSTATUS) == 0)
+  {
+    if (h->old || h->read)
+    {
+      fputs ("Status: ", out);
+      if (h->read)
+	fputs ("RO", out);
+      else if (h->old)
+	fputc ('O', out);
+      fputc ('\n', out);
+    }
 
-	if (h->flagged)
-	{
-	  if (fputc ('F', out) == EOF)
-	    return (-1);
-	}
-	
-	if (fputc ('\n', out) == EOF)
-	  return (-1);
-      }
+    if (h->flagged || h->replied)
+    {
+      fputs ("X-Status: ", out);
+      if (h->replied)
+	fputc ('A', out);
+      if (h->flagged)
+	fputc ('F', out);
+      fputc ('\n', out);
     }
   }
 
   if (flags & CH_UPDATE_LEN &&
       (flags & CH_NOLEN) == 0)
   {
-    fprintf (out, "Content-Length: %ld\n", h->content->length);
+    fprintf (out, "Content-Length: " OFF_T_FMT "\n", h->content->length);
     if (h->lines != 0 || h->content->length == 0)
       fprintf (out, "Lines: %d\n", h->lines);
   }
 
   if ((flags & CH_NONEWLINE) == 0)
   {
     if (flags & CH_PREFIX)
       fputs(prefix, out);
-    if (fputc ('\n', out) == EOF) /* add header terminator */
-      return (-1);
+    fputc ('\n', out); /* add header terminator */
   }
 
   if (ferror (out) || feof (out))
     return -1;
   
-  return (0);
+  return 0;
 }
 
 /* Count the number of lines and bytes to be deleted in this body*/
-static int count_delete_lines (FILE *fp, BODY *b, long *length, size_t datelen)
+static int count_delete_lines (FILE *fp, BODY *b, LOFF_T *length, size_t datelen)
 {
   int dellines = 0;
   long l;
   int ch;
 
   if (b->deleted)
   {
-    fseek (fp, b->offset, SEEK_SET);
+    fseeko (fp, b->offset, SEEK_SET);
     for (l = b->length ; l ; l --)
     {
       ch = getc (fp);
       if (ch == EOF)
 	break;
       if (ch == '\n')
