 	}
 	t = t->next;
       }
       mutt_free_list (&attach);
     }
 
-    rv = ci_send_message (sendflags, msg, tempfile, NULL, NULL);
+    rv = ci_send_message (sendflags, msg, bodyfile, NULL, NULL);
+
+    if (edit_infile)
+    {
+      if (includeFile)
+        msg->content->unlink = 0;
+      else if (draftFile)
+      {
+        if (truncate (expanded_infile, 0) == -1)
+        {
+          if (!option (OPTNOCURSES))
+            mutt_endwin (NULL);
+          perror (expanded_infile);
+          exit (1);
+        }
+        if ((fout = safe_fopen (expanded_infile, "a")) == NULL)
+        {
+          if (!option (OPTNOCURSES))
+            mutt_endwin (NULL);
+          perror (expanded_infile);
+          exit (1);
+        }
+
+        /* If the message was sent or postponed, these will already
+         * have been done.
+         */
+        if (rv < 0)
+        {
+          if (msg->content->next)
+            msg->content = mutt_make_multipart (msg->content);
+          mutt_encode_descriptions (msg->content, 1);
+          mutt_prepare_envelope (msg->env, 0);
+          mutt_env_to_intl (msg->env, NULL, NULL);
+        }
+
+        mutt_write_rfc822_header (fout, msg->env, msg->content, -1, 0);
+        if (option (OPTRESUMEEDITEDDRAFTFILES))
+          fprintf (fout, "X-Mutt-Resume-Draft: 1\n");
+        fputc ('\n', fout);
+        if ((mutt_write_mime_body (msg->content, fout) == -1))
+        {
+          if (!option (OPTNOCURSES))
+            mutt_endwin (NULL);
+          safe_fclose (&fout);
+          exit (1);
+        }
+        safe_fclose (&fout);
+      }
+
+      mutt_free_header (&msg);
+    }
+
+    /* !edit_infile && draftFile will leave the tempfile around */
+    if (tempfile)
+    {
+      unlink (tempfile);
+      FREE (&tempfile);
+    }
 
     if (!option (OPTNOCURSES))
       mutt_endwin (NULL);
 
     if (rv)
       exit(1);
