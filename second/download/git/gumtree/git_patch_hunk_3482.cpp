 static int warn_if_unremovable(const char *op, const char *file, int rc)
 {
 	int err;
 	if (!rc || errno == ENOENT)
 		return 0;
 	err = errno;
-	warning("unable to %s %s: %s", op, file, strerror(errno));
+	warning_errno("unable to %s %s", op, file);
 	errno = err;
 	return rc;
 }
 
 int unlink_or_msg(const char *file, struct strbuf *err)
 {
