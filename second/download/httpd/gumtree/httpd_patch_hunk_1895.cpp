         /* By default, AIX binds to a single processor.  This bit unbinds
          * children which will then bind to another CPU.
          */
         int status = bindprocessor(BINDPROCESS, (int)getpid(),
                                PROCESSOR_CLASS_ANY);
         if (status != OK)
-            ap_log_error(APLOG_MARK, APLOG_WARNING, errno,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, errno,
                          ap_server_conf,
-                         "processor unbind failed %d", status);
+                         "processor unbind failed");
 #endif
         RAISE_SIGSTOP(MAKE_CHILD);
 
         apr_signal(SIGTERM, just_die);
         child_main(slot);
 
