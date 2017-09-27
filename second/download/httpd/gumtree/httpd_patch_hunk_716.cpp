             * is already dup()ed by apr_procattr_child_{in,out}_set()
             * above.
             */
             close(sd2);
 
             if (memcmp(&empty_ugid, &cgid_req.ugid, sizeof(empty_ugid))) {
-                /* We have a valid identity, and can be sure that 
-                 * cgid_suexec_id_doer will return a valid ugid 
+                /* We have a valid identity, and can be sure that
+                 * cgid_suexec_id_doer will return a valid ugid
                  */
                 rc = ap_os_create_privileged_process(r, procnew, argv0, argv,
                                                      (const char * const *)env,
                                                      procattr, ptrans);
             } else {
-                rc = apr_proc_create(procnew, argv0, argv, 
-                                     (const char * const *)env, 
+                rc = apr_proc_create(procnew, argv0, argv,
+                                     (const char * const *)env,
                                      procattr, ptrans);
             }
-                
+
             if (rc != APR_SUCCESS) {
                 /* Bad things happened. Everyone should have cleaned up.
                  * ap_log_rerror() won't work because the header table used by
                  * ap_log_rerror() hasn't been replicated in the phony r
                  */
                 ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
-                             "couldn't create child process: %d: %s", rc, 
-                             apr_filename_of_pathname(r->filename));
+                             "couldn't create child process: %d: %s", rc,
+                             apr_filepath_name_get(r->filename));
             }
             else {
                 /* We don't want to leak storage for the key, so only allocate
                  * a key if the key doesn't exist yet in the hash; there are
                  * only a limited number of possible keys (one for each
                  * possible thread in the server), so we can allocate a copy
