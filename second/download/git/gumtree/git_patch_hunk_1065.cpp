 		 * scenarios (even 100% of the default ones).
 		 */
 		unsigned char head_sha1[20];
 		int head_flag;
 		const char *head_ref;
 
-		head_ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
-					      head_sha1, &head_flag);
+		head_ref = refs_resolve_ref_unsafe(&refs->base, "HEAD",
+						   RESOLVE_REF_READING,
+						   head_sha1, &head_flag);
 		if (head_ref && (head_flag & REF_ISSYMREF) &&
 		    !strcmp(head_ref, lock->ref_name)) {
 			struct strbuf log_err = STRBUF_INIT;
-			if (log_ref_write("HEAD", lock->old_oid.hash, sha1,
-					  logmsg, 0, &log_err)) {
+			if (files_log_ref_write(refs, "HEAD",
+						lock->old_oid.hash, sha1,
+						logmsg, 0, &log_err)) {
 				error("%s", log_err.buf);
 				strbuf_release(&log_err);
 			}
 		}
 	}
 
