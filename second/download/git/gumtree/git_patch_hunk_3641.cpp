 	const char *refname = cb_data;
 
 	if (verbose)
 		fprintf(stderr, "Checking reflog %s->%s\n",
 			sha1_to_hex(osha1), sha1_to_hex(nsha1));
 
-	fsck_handle_reflog_sha1(refname, osha1);
-	fsck_handle_reflog_sha1(refname, nsha1);
+	fsck_handle_reflog_sha1(refname, osha1, 0);
+	fsck_handle_reflog_sha1(refname, nsha1, timestamp);
 	return 0;
 }
 
 static int fsck_handle_reflog(const char *logname, const struct object_id *oid,
 			      int flag, void *cb_data)
 {
