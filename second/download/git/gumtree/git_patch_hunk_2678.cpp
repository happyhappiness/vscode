 #  define MAX_IO_SIZE SSIZE_MAX
 # else
 #  define MAX_IO_SIZE MAX_IO_SIZE_DEFAULT
 # endif
 #endif
 
+/**
+ * xopen() is the same as open(), but it die()s if the open() fails.
+ */
+int xopen(const char *path, int oflag, ...)
+{
+	mode_t mode = 0;
+	va_list ap;
+
+	/*
+	 * va_arg() will have undefined behavior if the specified type is not
+	 * compatible with the argument type. Since integers are promoted to
+	 * ints, we fetch the next argument as an int, and then cast it to a
+	 * mode_t to avoid undefined behavior.
+	 */
+	va_start(ap, oflag);
+	if (oflag & O_CREAT)
+		mode = va_arg(ap, int);
+	va_end(ap);
+
+	for (;;) {
+		int fd = open(path, oflag, mode);
+		if (fd >= 0)
+			return fd;
+		if (errno == EINTR)
+			continue;
+
+		if ((oflag & O_RDWR) == O_RDWR)
+			die_errno(_("could not open '%s' for reading and writing"), path);
+		else if ((oflag & O_WRONLY) == O_WRONLY)
+			die_errno(_("could not open '%s' for writing"), path);
+		else
+			die_errno(_("could not open '%s' for reading"), path);
+	}
+}
+
 /*
  * xread() is the same a read(), but it automatically restarts read()
  * operations with a recoverable error (EAGAIN and EINTR). xread()
  * DOES NOT GUARANTEE that "len" bytes is read even if the data is available.
  */
 ssize_t xread(int fd, void *buf, size_t len)
