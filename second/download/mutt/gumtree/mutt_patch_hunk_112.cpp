     }
 
     fflush (tempfp);
     if (ferror (tempfp))
     {
       dprint (1, (debugfile, "mutt_write_fcc(): %s: write failed.\n", tempfile));
-      fclose (tempfp);
+      safe_fclose (&tempfp);
       unlink (tempfile);
       mx_commit_message (msg, &f);	/* XXX - really? */
       mx_close_message (&msg);
       mx_close_mailbox (&f, NULL);
       return -1;
     }
 
     /* count the number of lines */
     rewind (tempfp);
     while (fgets (sasha, sizeof (sasha), tempfp) != NULL)
       lines++;
-    fprintf (msg->fp, "Content-Length: %ld\n", (long) ftell (tempfp));
+    fprintf (msg->fp, "Content-Length: " OFF_T_FMT "\n", (LOFF_T) ftello (tempfp));
     fprintf (msg->fp, "Lines: %d\n\n", lines);
 
     /* copy the body and clean up */
     rewind (tempfp);
     r = mutt_copy_stream (tempfp, msg->fp);
     if (fclose (tempfp) != 0)
