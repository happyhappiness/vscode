 		}
 	}
 	*buf = '\0';
 	return maxlen > 0;
 }
 
-
 void io_printf(int fd, const char *format, ...)
 {
 	va_list ap;
-	char buf[1024];
+	char buf[BIGPATHBUFLEN];
 	int len;
 
 	va_start(ap, format);
 	len = vsnprintf(buf, sizeof buf, format, ap);
 	va_end(ap);
 
 	if (len < 0)
 		exit_cleanup(RERR_STREAMIO);
 
+	if (len > (int)sizeof buf) {
+		rprintf(FERROR, "io_printf() was too long for the buffer.\n");
+		exit_cleanup(RERR_STREAMIO);
+	}
+
 	write_sbuf(fd, buf);
 }
 
-
 /** Setup for multiplexing a MSG_* stream with the data stream. */
 void io_start_multiplex_out(void)
 {
 	io_flush(NORMAL_FLUSH);
 	io_start_buffering_out();
 	io_multiplexing_out = 1;
