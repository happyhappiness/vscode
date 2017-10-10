 			      get_lock_file_path(&reflog_lock), strerror(errno));
 			goto failure;
 		}
 	}
 
 	(*prepare_fn)(refname, sha1, cb.policy_cb);
-	for_each_reflog_ent(refname, expire_reflog_ent, &cb);
+	refs_for_each_reflog_ent(ref_store, refname, expire_reflog_ent, &cb);
 	(*cleanup_fn)(cb.policy_cb);
 
 	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
 		/*
 		 * It doesn't make sense to adjust a reference pointed
 		 * to by a symbolic ref based on expiring entries in
 		 * the symbolic reference's reflog. Nor can we update
 		 * a reference if there are no remaining reflog
 		 * entries.
 		 */
 		int update = (flags & EXPIRE_REFLOGS_UPDATE_REF) &&
 			!(type & REF_ISSYMREF) &&
-			!is_null_sha1(cb.last_kept_sha1);
+			!is_null_oid(&cb.last_kept_oid);
 
 		if (close_lock_file(&reflog_lock)) {
 			status |= error("couldn't write %s: %s", log_file,
 					strerror(errno));
 		} else if (update &&
 			   (write_in_full(get_lock_file_fd(lock->lk),
-				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
+				oid_to_hex(&cb.last_kept_oid), GIT_SHA1_HEXSZ) != GIT_SHA1_HEXSZ ||
 			    write_str_in_full(get_lock_file_fd(lock->lk), "\n") != 1 ||
 			    close_ref(lock) < 0)) {
 			status |= error("couldn't write %s",
 					get_lock_file_path(lock->lk));
 			rollback_lock_file(&reflog_lock);
 		} else if (commit_lock_file(&reflog_lock)) {
