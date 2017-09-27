     cmd_only = apr_pstrdup(p, *cmd);
 
     /* truncate any arguments from the cmd */
     for (ptr = cmd_only; *ptr && (*ptr != ' '); ptr++);
     *ptr = '\0';
 
+    /* Figure out what the extension is so that we can matche it. */
     ext = strrchr(apr_filename_of_pathname(cmd_only), '.');
     
+    /* eliminate the '.' if there is one */
     if (*ext == '.')
         ++ext;
 
     /* If it is an NLM then just execute it. */
     if (stricmp(ext, "nlm")) {
+        /* check if we have a registered command for the extension*/
         *cmd = apr_table_get(d->file_type_handlers, ext);
         if (*cmd == NULL) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "Could not find a command associated with the %s extension", ext);
             return APR_EBADF;
         }
+
+        /* If we have a registered command then add the file that was passed in as a
+          parameter to the registered command. */
+        *cmd = apr_pstrcat (p, *cmd, " ", cmd_only, NULL);
+
+        /* Run in its own address space if specified */
         detached = apr_table_get(d->file_handler_mode, ext);
         if (detached) {
             e_info->detached = 1;
         }
     }
 
+    /* Tokenize the full command string into its arguments */
     apr_tokenize_to_argv(*cmd, (char***)argv, p);
     e_info->cmd_type = APR_PROGRAM;
-    *cmd = ap_server_root_relative(p, cmd_only);
+
+    /* The first argument should be the executible */
+    *cmd = ap_server_root_relative(p, *argv[0]);
 
     return APR_SUCCESS;
 }
 
 static void register_hooks(apr_pool_t *p)
 {
