 		strbuf_release(&err);
 		goto rollbacklog;
 	}
 
 	flag = log_all_ref_updates;
 	log_all_ref_updates = 0;
-	if (write_ref_to_lockfile(lock, orig_sha1) ||
-	    commit_ref_update(lock, orig_sha1, NULL))
-		error("unable to write current sha1 into %s", oldrefname);
+	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
+	    commit_ref_update(lock, orig_sha1, NULL, 0, &err)) {
+		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
+		strbuf_release(&err);
+	}
 	log_all_ref_updates = flag;
 
  rollbacklog:
 	if (logmoved && rename(git_path("logs/%s", newrefname), git_path("logs/%s", oldrefname)))
 		error("unable to restore logfile %s from %s: %s",
 			oldrefname, newrefname, strerror(errno));
