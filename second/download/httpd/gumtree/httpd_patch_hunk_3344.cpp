     DosGetInfoBlocks(&ptib, &ppib);
     DosQueryModuleName(ppib->pib_hmte, sizeof(progname), progname);
     rc = DosExecPgm(fail_module, sizeof(fail_module), EXEC_ASYNCRESULT,
                     ppib->pib_pchcmd, NULL, &proc_rc, progname);
 
     if (rc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00208)
                      "error spawning child, slot %d", slot);
     }
 
     if (ap_max_daemons_limit < slot) {
         ap_max_daemons_limit = slot;
     }
