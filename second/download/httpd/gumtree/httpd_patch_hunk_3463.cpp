     struct group *ent;
 
     if (name[0] == '#')
         return (atoi(&name[1]));
 
     if (!(ent = getgrnam(name))) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00544)
                      "%s: bad group name %s", ap_server_argv0, name);
         exit(1);
     }
 
     return (ent->gr_gid);
 }
