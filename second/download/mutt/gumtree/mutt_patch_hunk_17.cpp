       ignore = 0;
     } /* If beginning of header */
 
     if (!ignore)
     {
       dprint (2, (debugfile, "Reorder: x = %d; hdr_count = %d\n", x, hdr_count));
-      /* Save the header in headers[x] */
-      if (!headers[x])
-	headers[x] = safe_strdup (buf);
-      else
-      {
-	safe_realloc ((void **) &headers[x],
-		      mutt_strlen (headers[x]) + mutt_strlen (buf) + sizeof (char));
-	strcat (headers[x], buf);	/* __STRCAT_CHECKED__ */
+      if (!this_one) {
+	this_one = safe_strdup (buf);
+	this_one_len = mutt_strlen (this_one);
+      } else {
+	int blen = mutt_strlen (buf);
+
+	safe_realloc (&this_one, this_one_len + blen + sizeof (char));
+	strcat (this_one + this_one_len, buf); /* __STRCAT_CHECKED__ */
+	this_one_len += blen;
       }
     }
-  } /* while (ftell (in) < off_end) */
+  } /* while (ftello (in) < off_end) */
+
+  /* Do we have anything pending?  -- XXX, same code as in above in the loop. */
+  if (this_one)
+  {
+    if (flags & CH_DECODE) 
+    {
+      if (!address_header_decode (&this_one))
+	rfc2047_decode (&this_one);
+    }
+    
+    if (!headers[x])
+      headers[x] = this_one;
+    else 
+    {
+      int hlen = mutt_strlen (headers[x]);
+
+      safe_realloc (&headers[x], hlen + this_one_len + sizeof (char));
+      strcat (headers[x] + hlen, this_one); /* __STRCAT_CHECKED__ */
+      FREE (&this_one);
+    }
+
+    this_one = NULL;
+  }
 
   /* Now output the headers in order */
   for (x = 0; x < hdr_count; x++)
   {
     if (headers[x])
     {
+#if 0
       if (flags & CH_DECODE)
 	rfc2047_decode (&headers[x]);
+#endif
 
       /* We couldn't do the prefixing when reading because RFC 2047
        * decoding may have concatenated lines.
        */
-      if (flags & CH_PREFIX)
+      
+      if (flags & (CH_DECODE|CH_PREFIX))
       {
-	char *ch = headers[x];
-	int print_prefix = 1;
-
-	while (*ch)
-	{ 
-	  if (print_prefix)
-	  {
-	    if (fputs (prefix, out) == EOF)
-	    {
-	      error = TRUE;
-	      break;
-	    }
-	    print_prefix = 0;
-	  }
-
-	  if (*ch == '\n' && ch[1])
-	    print_prefix = 1;
-
-	  if (putc (*ch++, out) == EOF)
-	  {
-	    error = TRUE;
-	    break;
-	  }
-	}
-	if (error)
+	if (mutt_write_one_header (out, 0, headers[x], 
+				   flags & CH_PREFIX ? prefix : 0, mutt_term_width (Wrap), flags) == -1)
+	{
+	  error = TRUE;
 	  break;
+	}
       }
       else
       {      
 	if (fputs (headers[x], out) == EOF)
 	{
 	  error = TRUE;
