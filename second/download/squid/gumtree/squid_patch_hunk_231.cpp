         }
 
         sendSignal();
         /* NOTREACHED */
     }
 
+    debugs(1,2, HERE << "Doing post-config initialization\n");
+    leave_suid();
+    ActivateRegistered(rrFinalizeConfig);
+    ActivateRegistered(rrClaimMemoryNeeds);
+    ActivateRegistered(rrAfterConfig);
+    enter_suid();
+
+    if (!opt_no_daemon && Config.workers > 0)
+        watch_child(argv);
+
     if (opt_create_swap_dirs) {
         /* chroot if configured to run inside chroot */
 
         if (Config.chroot_dir && chroot(Config.chroot_dir)) {
             fatal("failed to chroot");
         }
 
         setEffectiveUser();
-        debugs(0, 0, "Creating Swap Directories");
+        debugs(0, DBG_CRITICAL, "Creating missing swap directories");
         Store::Root().create();
 
         return 0;
     }
 
-    if (!opt_no_daemon)
-        watch_child(argv);
+    if (IamPrimaryProcess())
+        CpuAffinityCheck();
+    CpuAffinityInit();
 
     setMaxFD();
 
     /* init comm module */
     comm_init();
 
-    comm_select_init();
-
     if (opt_no_daemon) {
         /* we have to init fdstat here. */
         fd_open(0, FD_LOG, "stdin");
         fd_open(1, FD_LOG, "stdout");
         fd_open(2, FD_LOG, "stderr");
     }
