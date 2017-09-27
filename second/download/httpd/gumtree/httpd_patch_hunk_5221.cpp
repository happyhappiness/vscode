         ap_log_error(APLOG_MARK, APLOG_STARTUP, status, NULL, APLOGNO(00103)
                      "piped_log_spawn: unable to setup child process '%s'",
                      pl->program);
     }
     else {
         char **args;
-        const char *pname;
 
         apr_tokenize_to_argv(pl->program, &args, pl->p);
-        pname = apr_pstrdup(pl->p, args[0]);
         procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
-        status = apr_proc_create(procnew, pname, (const char * const *) args,
+        status = apr_proc_create(procnew, args[0], (const char * const *) args,
                                  NULL, procattr, pl->p);
 
         if (status == APR_SUCCESS) {
             pl->pid = procnew;
             /* procnew->in was dup2'd from pl->write_fd;
              * since the original fd is still valid, close the copy to
