             continue;
         }
         if (!(map->argv[0]) || !*(map->argv[0]) || map->fpin || map->fpout) {
             continue;
         }
 
-        if (!lock_warning_issued && (!lockname || !*lockname)) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
-                         "mod_rewrite: Running external rewrite maps "
-                         "without defining a RewriteLock is DANGEROUS!");
-            ++lock_warning_issued;
-        }
-
         rc = rewritemap_program_child(p, map->argv[0], map->argv,
                                       &fpout, &fpin);
         if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                          "mod_rewrite: could not start RewriteMap "
                          "program %s", map->checkfile);
