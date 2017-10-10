 {
 	int sink, check;
 	struct sha1file *f;
 
 	sink = open("/dev/null", O_WRONLY);
 	if (sink < 0)
-		return NULL;
+		die_errno("unable to open /dev/null");
 	check = open(name, O_RDONLY);
-	if (check < 0) {
-		int saved_errno = errno;
-		close(sink);
-		errno = saved_errno;
-		return NULL;
-	}
+	if (check < 0)
+		die_errno("unable to open '%s'", name);
 	f = sha1fd(sink, name);
 	f->check_fd = check;
 	return f;
 }
 
 struct sha1file *sha1fd_throughput(int fd, const char *name, struct progress *tp)
