 	need_pause = 1;
       }
     }
   }
 
   /* Read the user's initialization file.  */
-  if (access (Muttrc, F_OK) != -1)
+  if (Muttrc)
   {
     if (!option (OPTNOCURSES))
       endwin ();
     if (source_rc (Muttrc, &err) != 0)
     {
       fputs (err.data, stderr);
       fputc ('\n', stderr);
       need_pause = 1;
     }
   }
-  else if (!default_rc)
-  {
-    /* file specified by -F does not exist */
-    snprintf (buffer, sizeof (buffer), "%s: %s", Muttrc, strerror (errno));
-    mutt_endwin (buffer);
-    exit (1);
-  }
 
   if (mutt_execute_commands (commands) != 0)
     need_pause = 1;
 
   if (need_pause && !option (OPTNOCURSES))
   {
