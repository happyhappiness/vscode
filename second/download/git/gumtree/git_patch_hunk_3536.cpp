 			die_errno(_("could not open '%s' for writing"), path);
 		else
 			die_errno(_("could not open '%s' for reading"), path);
 	}
 }
 
+static int handle_nonblock(int fd, short poll_events, int err)
+{
+	struct pollfd pfd;
+
+	if (err != EAGAIN && err != EWOULDBLOCK)
+		return 0;
+
+	pfd.fd = fd;
+	pfd.events = poll_events;
+
+	/*
+	 * no need to check for errors, here;
+	 * a subsequent read/write will detect unrecoverable errors
+	 */
+	poll(&pfd, 1, -1);
+	return 1;
+}
+
 /*
  * xread() is the same a read(), but it automatically restarts read()
  * operations with a recoverable error (EAGAIN and EINTR). xread()
  * DOES NOT GUARANTEE that "len" bytes is read even if the data is available.
  */
 ssize_t xread(int fd, void *buf, size_t len)
