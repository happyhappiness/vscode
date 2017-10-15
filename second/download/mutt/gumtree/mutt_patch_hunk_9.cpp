   }
 
   if (!Pager || mutt_strcmp (Pager, "builtin") == 0)
     builtin = 1;
   else
   {
-    mutt_make_string (buf, sizeof (buf), NONULL(PagerFmt), Context, cur);
+    struct hdr_format_info hfi;
+    hfi.ctx = Context;
+    hfi.pager_progress = ExtPagerProgress;
+    hfi.hdr = cur;
+    mutt_make_string_info (buf, sizeof (buf), NONULL(PagerFmt), &hfi, M_FORMAT_MAKEPRINT);
     fputs (buf, fpout);
     fputs ("\n\n", fpout);
   }
 
   res = mutt_copy_message (fpout, Context, cur, cmflags,
-       	(option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) | CH_DECODE | CH_FROM);
-  if ((safe_fclose (&fpout) != 0 && errno != EPIPE) || res == -1)
+       	(option (OPTWEED) ? (CH_WEED | CH_REORDER) : 0) | CH_DECODE | CH_FROM | CH_DISPLAY);
+  if ((safe_fclose (&fpout) != 0 && errno != EPIPE) || res < 0)
   {
     mutt_error (_("Could not copy message"));
     if (fpfilterout != NULL)
     {
       mutt_wait_filter (filterpid);
       safe_fclose (&fpfilterout);
