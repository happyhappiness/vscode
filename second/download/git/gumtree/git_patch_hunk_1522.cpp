 		 * but finding all symrefs pointing to the given branch
 		 * would be rather costly for this rare event (the direct
 		 * update of a branch) to be worth it.  So let's cheat and
 		 * check with HEAD only which should cover 99% of all usage
 		 * scenarios (even 100% of the default ones).
 		 */
-		unsigned char head_sha1[20];
+		struct object_id head_oid;
 		int head_flag;
 		const char *head_ref;
 
 		head_ref = refs_resolve_ref_unsafe(&refs->base, "HEAD",
 						   RESOLVE_REF_READING,
-						   head_sha1, &head_flag);
+						   head_oid.hash, &head_flag);
 		if (head_ref && (head_flag & REF_ISSYMREF) &&
 		    !strcmp(head_ref, lock->ref_name)) {
 			struct strbuf log_err = STRBUF_INIT;
 			if (files_log_ref_write(refs, "HEAD",
-						lock->old_oid.hash, sha1,
+						&lock->old_oid, oid,
 						logmsg, 0, &log_err)) {
 				error("%s", log_err.buf);
 				strbuf_release(&log_err);
 			}
 		}
 	}
