     if (!option (OPTNOCURSES))
     {
       char msg[LONG_STRING];
       
       snprintf(msg, sizeof(msg), _("Lock count exceeded, remove lock for %s?"),
 	       path);
-      if(retry && mutt_yesorno(msg, 1) == 1)
+      if(retry && mutt_yesorno(msg, M_YES) == M_YES)
       {
 	flags |= DL_FL_FORCE;
 	retry--;
 	mutt_clear_error ();
 	goto retry_lock;
       }
