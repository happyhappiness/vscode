 		code = itemizing ? FNONE : FINFO;
 	} else {
 		itemizing = 0;
 		maybe_ATTRS_REPORT = ATTRS_REPORT;
 		code = FINFO;
 	}
+	solo_file = local_name;
+	dir_tweaking = !(list_only || solo_file || dry_run);
+	need_retouch_dir_times = preserve_times > 1;
+	lull_mod = allowed_lull * 5;
 
-	if (verbose > 2) {
-		rprintf(FINFO, "generator starting pid=%ld count=%d\n",
-			(long)getpid(), flist->count);
-	}
+	if (verbose > 2)
+		rprintf(FINFO, "generator starting pid=%ld\n", (long)getpid());
 
-	if (delete_before && !local_name && flist->count > 0)
-		do_delete_pass(flist);
+	if (delete_before && !solo_file && cur_flist->used > 0)
+		do_delete_pass();
+	if (delete_during == 2) {
+		deldelay_size = BIGPATHBUFLEN * 4;
+		deldelay_buf = new_array(char, deldelay_size);
+		if (!deldelay_buf)
+			out_of_memory("delete-delay");
+	}
 	do_progress = 0;
 
-	if (append_mode || whole_file < 0)
+	if (append_mode > 0 || whole_file < 0)
 		whole_file = 0;
 	if (verbose >= 2) {
 		rprintf(FINFO, "delta-transmission %s\n",
 			whole_file
 			? "disabled for local transfer or --whole-file"
 			: "enabled");
