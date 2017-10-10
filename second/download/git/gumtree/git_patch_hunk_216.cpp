 		}
 	}
 
 	return 0;
 }
 
+/* This function should make sure errno is meaningful on error */
 static struct ref_lock *verify_lock(struct ref_lock *lock,
 	const unsigned char *old_sha1, int mustexist)
 {
 	if (read_ref_full(lock->ref_name, lock->old_sha1, mustexist, NULL)) {
+		int save_errno = errno;
 		error("Can't verify ref %s", lock->ref_name);
 		unlock_ref(lock);
+		errno = save_errno;
 		return NULL;
 	}
 	if (hashcmp(lock->old_sha1, old_sha1)) {
 		error("Ref %s is at %s but expected %s", lock->ref_name,
 			sha1_to_hex(lock->old_sha1), sha1_to_hex(old_sha1));
 		unlock_ref(lock);
+		errno = EBUSY;
 		return NULL;
 	}
 	return lock;
 }
 
 static int remove_empty_directories(const char *file)
 {
 	/* we want to create a file but there is a directory there;
 	 * if that is an empty directory (or a directory that contains
 	 * only empty directories), remove them.
 	 */
 	struct strbuf path;
-	int result;
+	int result, save_errno;
 
 	strbuf_init(&path, 20);
 	strbuf_addstr(&path, file);
 
 	result = remove_dir_recursively(&path, REMOVE_DIR_EMPTY_ONLY);
+	save_errno = errno;
 
 	strbuf_release(&path);
+	errno = save_errno;
 
 	return result;
 }
 
 /*
  * *string and *len will only be substituted, and *string returned (for
