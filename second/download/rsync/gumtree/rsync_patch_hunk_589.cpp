 	if (!io_buffer) out_of_memory("writefd");
 	io_buffer_count = 0;
 }
 
 /* write an message to a multiplexed stream. If this fails then rsync
    exits */
-static void mplex_write(int fd, enum logcode code, char *buf, size_t len)
+static void mplex_write(int fd, enum logcode code, char *buf, int len)
 {
 	char buffer[4096];
 	int n = len;
 
 	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);
 
