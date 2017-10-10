 		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
 		strbuf_release(&err);
 	}
 	log_all_ref_updates = flag;
 
  rollbacklog:
-	if (logmoved && rename(git_path("logs/%s", newrefname), git_path("logs/%s", oldrefname)))
+	if (logmoved && rename(sb_newref.buf, sb_oldref.buf))
 		error("unable to restore logfile %s from %s: %s",
 			oldrefname, newrefname, strerror(errno));
 	if (!logmoved && log &&
-	    rename(git_path(TMP_RENAMED_LOG), git_path("logs/%s", oldrefname)))
-		error("unable to restore logfile %s from "TMP_RENAMED_LOG": %s",
+	    rename(tmp_renamed_log.buf, sb_oldref.buf))
+		error("unable to restore logfile %s from logs/"TMP_RENAMED_LOG": %s",
 			oldrefname, strerror(errno));
+	ret = 1;
+ out:
+	strbuf_release(&sb_newref);
+	strbuf_release(&sb_oldref);
+	strbuf_release(&tmp_renamed_log);
 
-	return 1;
+	return ret;
 }
 
 static int close_ref(struct ref_lock *lock)
 {
 	if (close_lock_file(lock->lk))
 		return -1;
