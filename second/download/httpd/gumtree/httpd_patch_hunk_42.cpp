                                       ":", gid, NULL);
 
     if ((errstr = make_perchild_socket(sconf->fullsockname, socks))) {
         return errstr;
     }
 
-    sconf->sd = socks[0]; 
-    sconf->sd2 = socks[1];
+    sconf->input = socks[0]; 
+    sconf->output = socks[1];
 
     for (i = 0; i < num_daemons; i++) {
         if (u == child_info_table[i].uid && g == child_info_table[i].gid) {
-            child_info_table[i].sd = sconf->sd;
+            child_info_table[i].input = sconf->input;
+            child_info_table[i].output = sconf->output;
             matching++;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, 
                          "filling out child_info_table; UID: %d, GID: %d, "
-                         "SD: %d, Child Num: %d", child_info_table[i].uid, 
-                         child_info_table[i].gid, sconf->sd, i);
+                         "SD: %d %d, OUTPUT: %d %d, Child Num: %d", 
+                         child_info_table[i].uid, child_info_table[i].gid, 
+                         sconf->input, child_info_table[i].input, sconf->output,
+                         child_info_table[i].output, i);
         }
     }
 
     if (!matching) {
         return "Unable to find process with matching uid/gid.";
     }
