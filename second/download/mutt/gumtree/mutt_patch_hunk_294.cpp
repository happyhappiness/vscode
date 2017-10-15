 	last = env->userhdrs = mutt_new_list ();
       last->data = safe_strdup (uh->data);
     }
   }
 }
 
-void mutt_forward_intro (FILE *fp, HEADER *cur)
+void mutt_forward_intro (CONTEXT *ctx, HEADER *cur, FILE *fp)
 {
-  char buffer[STRING];
-  
-  fputs ("----- Forwarded message from ", fp);
-  buffer[0] = 0;
-  rfc822_write_address (buffer, sizeof (buffer), cur->env->from, 1);
-  fputs (buffer, fp);
-  fputs (" -----\n\n", fp);
+  char buffer[LONG_STRING];
+
+  if (ForwardAttrIntro)
+  {
+    setlocale (LC_TIME, NONULL (AttributionLocale));
+    mutt_make_string (buffer, sizeof (buffer), ForwardAttrIntro, ctx, cur);
+    setlocale (LC_TIME, "");
+    fputs (buffer, fp);
+    fputs ("\n\n", fp);
+  }
 }
 
-void mutt_forward_trailer (FILE *fp)
+void mutt_forward_trailer (CONTEXT *ctx, HEADER *cur, FILE *fp)
 {
-  fputs ("\n----- End forwarded message -----\n", fp);
+  char buffer[LONG_STRING];
+
+  if (ForwardAttrTrailer)
+  {
+    setlocale (LC_TIME, NONULL (AttributionLocale));
+    mutt_make_string (buffer, sizeof (buffer), ForwardAttrTrailer, ctx, cur);
+    setlocale (LC_TIME, "");
+    fputc ('\n', fp);
+    fputs (buffer, fp);
+    fputc ('\n', fp);
+  }
 }
 
 
 static int include_forward (CONTEXT *ctx, HEADER *cur, FILE *out)
 {
   int chflags = CH_DECODE, cmflags = 0;
