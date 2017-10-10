 	if (!refname) {
 		last_errno = errno;
 		error("unable to resolve reference %s: %s",
 			orig_refname, strerror(errno));
 		goto error_return;
 	}
-	missing = is_null_sha1(lock->old_sha1);
-	/* When the ref did not exist and we are creating it,
-	 * make sure there is no existing ref that is packed
-	 * whose name begins with our refname, nor a ref whose
-	 * name is a proper prefix of our refname.
+	/*
+	 * If the ref did not exist and we are creating it, make sure
+	 * there is no existing packed ref whose name begins with our
+	 * refname, nor a packed ref whose name is a proper prefix of
+	 * our refname.
 	 */
-	if (missing &&
+	if (is_null_sha1(lock->old_sha1) &&
 	     !is_refname_available(refname, skip, get_packed_refs(&ref_cache))) {
 		last_errno = ENOTDIR;
 		goto error_return;
 	}
 
 	lock->lk = xcalloc(1, sizeof(struct lock_file));
