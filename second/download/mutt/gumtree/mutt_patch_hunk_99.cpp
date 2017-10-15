 	      _("WARNING!  You are about to overwrite %s, continue?"),
 	      body->filename);
     if (mutt_yesorno (warning, M_NO) != M_YES) {
       CLEARLINE (LINES-1);
       return;
     }
-    mutt_mktemp (tfile);
+    mutt_mktemp (tfile, sizeof (tfile));
   }
   else
     tfile[0] = 0;
 
   if (mutt_pipe_attachment (fp, body, command, tfile))
   {
