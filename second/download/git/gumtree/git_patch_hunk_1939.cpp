 	}
 	return fd;
 }
 
 static int warn_if_unremovable(const char *op, const char *file, int rc)
 {
-	if (rc < 0) {
-		int err = errno;
-		if (ENOENT != err) {
-			warning("unable to %s %s: %s",
-				op, file, strerror(errno));
-			errno = err;
-		}
-	}
+	int err;
+	if (!rc || errno == ENOENT)
+		return 0;
+	err = errno;
+	warning("unable to %s %s: %s", op, file, strerror(errno));
+	errno = err;
 	return rc;
 }
 
+int unlink_or_msg(const char *file, struct strbuf *err)
+{
+	int rc = unlink(file);
+
+	assert(err);
+
+	if (!rc || errno == ENOENT)
+		return 0;
+
+	strbuf_addf(err, "unable to unlink %s: %s",
+		    file, strerror(errno));
+	return -1;
+}
+
 int unlink_or_warn(const char *file)
 {
 	return warn_if_unremovable("unlink", file, unlink(file));
 }
 
 int rmdir_or_warn(const char *file)
