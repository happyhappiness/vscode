 }
 
 
 /**
  * Read from the file descriptor handling multiplexing - return number
  * of bytes read.
- * 
- * Never returns <= 0. 
+ *
+ * Never returns <= 0.
  */
-static int read_unbuffered(int fd, char *buf, size_t len)
+static int readfd_unbuffered(int fd, char *buf, size_t len)
 {
 	static size_t remaining;
+	static size_t iobuf_in_ndx;
 	int tag, ret = 0;
 	char line[1024];
-	static char *buffer;
-	static size_t bufferIdx = 0;
-	static size_t bufferSz;
 
-	if (fd != multiplex_in_fd)
+	if (!iobuf_in || fd != sock_f_in)
 		return read_timeout(fd, buf, len);
 
 	if (!io_multiplexing_in && remaining == 0) {
-		if (!buffer) {
-			bufferSz = 2 * IO_BUFFER_SIZE;
-			buffer   = new_array(char, bufferSz);
-			if (!buffer) out_of_memory("read_unbuffered");
-		}
-		remaining = read_timeout(fd, buffer, bufferSz);
-		bufferIdx = 0;
+		remaining = read_timeout(fd, iobuf_in, iobuf_in_siz);
+		iobuf_in_ndx = 0;
 	}
 
 	while (ret == 0) {
 		if (remaining) {
 			len = MIN(len, remaining);
-			memcpy(buf, buffer + bufferIdx, len);
-			bufferIdx += len;
+			memcpy(buf, iobuf_in + iobuf_in_ndx, len);
+			iobuf_in_ndx += len;
 			remaining -= len;
 			ret = len;
 			break;
 		}
 
 		read_loop(fd, line, 4);
