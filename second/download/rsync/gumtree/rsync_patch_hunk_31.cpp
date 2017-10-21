     targets=NULL;
   }
 
   if (verbose > 2)
     fprintf(stderr, "false_alarms=%d tag_hits=%d matches=%d\n",
 	    false_alarms, tag_hits, matches);
+
+  total_tag_hits += tag_hits;
+  total_false_alarms += false_alarms;
+  total_matches += matches;
+  total_data_transfer += data_transfer;
+}
+
+void match_report(void)
+{
+  if (verbose <= 1)
+    return;
+
+  fprintf(am_server?stderr:stdout,
+	  "total: matches=%d  tag_hits=%d  false_alarms=%d  data=%d\n",
+	  total_matches,total_tag_hits,
+	  total_false_alarms,total_data_transfer);
 }
