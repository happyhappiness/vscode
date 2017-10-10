 		total += written;
 	}
 
 	return total;
 }
 
+ssize_t pread_in_full(int fd, void *buf, size_t count, off_t offset)
+{
+	char *p = buf;
+	ssize_t total = 0;
+
+	while (count > 0) {
+		ssize_t loaded = xpread(fd, p, count, offset);
+		if (loaded < 0)
+			return -1;
+		if (loaded == 0)
+			return total;
+		count -= loaded;
+		p += loaded;
+		total += loaded;
+		offset += loaded;
+	}
+
+	return total;
+}
+
 int xdup(int fd)
 {
 	int ret = dup(fd);
 	if (ret < 0)
 		die_errno("dup failed");
 	return ret;
