 	need_retouch_dir_times = preserve_times & PRESERVE_DIR_TIMES;
 	loopchk_limit = allowed_lull ? allowed_lull * 5 : 200;
 	symlink_timeset_failed_flags = ITEM_REPORT_TIME
 	    | (protocol_version >= 30 || !am_server ? ITEM_REPORT_TIMEFAIL : 0);
 	implied_dirs_are_missing = relative_paths && !implied_dirs && protocol_version < 30;
 
-	if (verbose > 2)
-		rprintf(FINFO, "generator starting pid=%ld\n", (long)getpid());
+	if (DEBUG_GTE(GENR, 1))
+		rprintf(FINFO, "generator starting pid=%d\n", (int)getpid());
 
 	if (delete_before && !solo_file && cur_flist->used > 0)
 		do_delete_pass();
 	if (delete_during == 2) {
 		deldelay_size = BIGPATHBUFLEN * 4;
 		deldelay_buf = new_array(char, deldelay_size);
 		if (!deldelay_buf)
 			out_of_memory("delete-delay");
 	}
-	do_progress = 0;
+	info_levels[INFO_FLIST] = info_levels[INFO_PROGRESS] = 0;
 
 	if (append_mode > 0 || whole_file < 0)
 		whole_file = 0;
-	if (verbose >= 2) {
+	if (DEBUG_GTE(FLIST, 1)) {
 		rprintf(FINFO, "delta-transmission %s\n",
 			whole_file
 			? "disabled for local transfer or --whole-file"
 			: "enabled");
 	}
 
-	/* Since we often fill up the outgoing socket and then just sit around
-	 * waiting for the other 2 processes to do their thing, we don't want
-	 * to exit on a timeout.  If the data stops flowing, the receiver will
-	 * notice that and let us know via the message pipe (or its closing). */
-	ignore_timeout = 1;
-
 	dflt_perms = (ACCESSPERMS & ~orig_umask);
 
 	do {
 #ifdef SUPPORT_HARD_LINKS
 		if (preserve_hard_links && inc_recurse) {
-			while (!flist_eof && file_total < FILECNT_LOOKAHEAD/2)
+			while (!flist_eof && file_total < MIN_FILECNT_LOOKAHEAD/2)
 				wait_for_receiver();
 		}
 #endif
 
 		if (inc_recurse && cur_flist->parent_ndx >= 0) {
 			struct file_struct *fp = dir_flist->files[cur_flist->parent_ndx];
