     severity = "WARNING";
   else if (n->severity == NOTIF_OKAY)
     severity = "OKAY";
 
   fprintf (fh,
       "Severity: %s\n"
-      "Time: %u\n",
-      severity, (unsigned int) n->time);
+      "Time: %.3f\n",
+      severity, CDTIME_T_TO_DOUBLE (n->time));
 
   /* Print the optional fields */
   if (strlen (n->host) > 0)
     fprintf (fh, "Host: %s\n", n->host);
   if (strlen (n->plugin) > 0)
     fprintf (fh, "Plugin: %s\n", n->plugin);
