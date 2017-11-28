      * may take on root privs during reconfigure.  If squid.conf
      * contains a "Bungled" line, fatal() will be called when the
      * process still has root privs.
      */
     leave_suid();
 
-    if (0 == StoreController::store_dirs_rebuilding)
-        storeDirWriteCleanLogs(0);
+    storeDirWriteCleanLogs(0);
 
     fatal_common(message);
 
     exit(1);
 }
 
