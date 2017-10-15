 
 	if ((fout = safe_fopen (tempfile, "w")) == NULL)
 	{
 	  if (!option (OPTNOCURSES))
 	    mutt_endwin (NULL);
 	  perror (tempfile);
-	  fclose (fin);
+	  safe_fclose (&fin);
 	  FREE (&tempfile);
 	  exit (1);
 	}
 	if (fin)
 	  mutt_copy_stream (fin, fout);
 	else if (bodytext)
 	  fputs (bodytext, fout);
-	fclose (fout);
+	safe_fclose (&fout);
 	if (fin && fin != stdin)
-	  fclose (fin);
+	  safe_fclose (&fin);
       }
     }
 
-    safe_free ((void **) &bodytext);
+    FREE (&bodytext);
     
     if (attach)
     {
       LIST *t = attach;
       BODY *a = NULL;
 
