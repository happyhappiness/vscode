 				   REF_NODEREF, NULL, &err);
 	if (!lock) {
 		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
 		strbuf_release(&err);
 		goto rollback;
 	}
-	hashcpy(lock->old_oid.hash, orig_sha1);
+	oidcpy(&lock->old_oid, &orig_oid);
 
-	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
-	    commit_ref_update(refs, lock, orig_sha1, logmsg, &err)) {
+	if (write_ref_to_lockfile(lock, &orig_oid, &err) ||
+	    commit_ref_update(refs, lock, &orig_oid, logmsg, &err)) {
 		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
 		strbuf_release(&err);
 		goto rollback;
 	}
 
 	ret = 0;
