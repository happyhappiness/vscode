 	multiplex_out_fd = fd;
 	io_buffer = (char *)malloc(IO_BUFFER_SIZE);
 	if (!io_buffer) out_of_memory("writefd");
 	io_buffer_count = 0;
 }
 
-/* write an message to a multiplexed stream. If this fails then rsync
-   exits */
+/**
+ * Write an message to a multiplexed stream. If this fails then rsync
+ * exits.
+ **/
 static void mplex_write(int fd, enum logcode code, char *buf, size_t len)
 {
 	char buffer[4096];
 	size_t n = len;
 
 	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);
