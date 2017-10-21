 		goto start;
 
 	return s - fname;
 }
 
 
+static char *iobuf_out;
+static int iobuf_out_cnt;
+
+void io_start_buffering_out(void)
+{
+	if (iobuf_out)
+		return;
+	if (!(iobuf_out = new_array(char, IO_BUFFER_SIZE)))
+		out_of_memory("io_start_buffering_out");
+	iobuf_out_cnt = 0;
+}
+
+
+static char *iobuf_in;
+static size_t iobuf_in_siz;
+
+void io_start_buffering_in(void)
+{
+	if (iobuf_in)
+		return;
+	iobuf_in_siz = 2 * IO_BUFFER_SIZE;
+	if (!(iobuf_in = new_array(char, iobuf_in_siz)))
+		out_of_memory("io_start_buffering_in");
+}
+
+
+void io_end_buffering(void)
+{
+	io_flush(NORMAL_FLUSH);
+	if (!io_multiplexing_out) {
+		free(iobuf_out);
+		iobuf_out = NULL;
+	}
+}
+
+
 /**
  * Continue trying to read len bytes - don't return until len has been
  * read.
  **/
 static void read_loop(int fd, char *buf, size_t len)
 {
