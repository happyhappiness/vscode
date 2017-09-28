         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Replication\r\n"
             "role:%s\r\n",
             server.masterhost == NULL ? "master" : "slave");
         if (server.masterhost) {
+            long long slave_repl_offset = 1;
+
+            if (server.master)
+                slave_repl_offset = server.master->reploff;
+            else if (server.cached_master)
+                slave_repl_offset = server.cached_master->reploff;
+
             info = sdscatprintf(info,
                 "master_host:%s\r\n"
                 "master_port:%d\r\n"
                 "master_link_status:%s\r\n"
                 "master_last_io_seconds_ago:%d\r\n"
                 "master_sync_in_progress:%d\r\n"
