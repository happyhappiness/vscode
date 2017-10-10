 			 * Maybe somebody just deleted one of the
 			 * directories leading to ref_file.  Try
 			 * again:
 			 */
 			goto retry;
 		else
-			unable_to_lock_index_die(ref_file, errno);
+			unable_to_lock_die(ref_file, errno);
 	}
 	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;
 
  error_return:
 	unlock_ref(lock);
 	errno = last_errno;
 	return NULL;
 }
 
-struct ref_lock *lock_ref_sha1(const char *refname, const unsigned char *old_sha1)
-{
-	char refpath[PATH_MAX];
-	if (check_refname_format(refname, 0))
-		return NULL;
-	strcpy(refpath, mkpath("refs/%s", refname));
-	return lock_ref_sha1_basic(refpath, old_sha1, 0, NULL);
-}
-
 struct ref_lock *lock_any_ref_for_update(const char *refname,
 					 const unsigned char *old_sha1,
 					 int flags, int *type_p)
 {
-	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
-		return NULL;
-	return lock_ref_sha1_basic(refname, old_sha1, flags, type_p);
+	return lock_ref_sha1_basic(refname, old_sha1, NULL, flags, type_p);
 }
 
 /*
  * Write an entry to the packed-refs file for the specified refname.
  * If peeled is non-NULL, write it as the entry's peeled value.
  */
-static void write_packed_entry(int fd, char *refname, unsigned char *sha1,
+static void write_packed_entry(FILE *fh, char *refname, unsigned char *sha1,
 			       unsigned char *peeled)
 {
-	char line[PATH_MAX + 100];
-	int len;
-
-	len = snprintf(line, sizeof(line), "%s %s\n",
-		       sha1_to_hex(sha1), refname);
-	/* this should not happen but just being defensive */
-	if (len > sizeof(line))
-		die("too long a refname '%s'", refname);
-	write_or_die(fd, line, len);
-
-	if (peeled) {
-		if (snprintf(line, sizeof(line), "^%s\n",
-			     sha1_to_hex(peeled)) != PEELED_LINE_LENGTH)
-			die("internal error");
-		write_or_die(fd, line, PEELED_LINE_LENGTH);
-	}
+	fprintf_or_die(fh, "%s %s\n", sha1_to_hex(sha1), refname);
+	if (peeled)
+		fprintf_or_die(fh, "^%s\n", sha1_to_hex(peeled));
 }
 
 /*
  * An each_ref_entry_fn that writes the entry to a packed-refs file.
  */
 static int write_packed_entry_fn(struct ref_entry *entry, void *cb_data)
 {
-	int *fd = cb_data;
 	enum peel_status peel_status = peel_entry(entry, 0);
 
 	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
 		error("internal error: %s is not a valid packed reference!",
 		      entry->name);
-	write_packed_entry(*fd, entry->name, entry->u.value.sha1,
+	write_packed_entry(cb_data, entry->name, entry->u.value.sha1,
 			   peel_status == PEEL_PEELED ?
 			   entry->u.value.peeled : NULL);
 	return 0;
 }
 
 /* This should return a meaningful errno on failure */
