 
 	write_int(f, -1);
 	SIVAL(b,0,(x&0xFFFFFFFF));
 	SIVAL(b,4,((x>>32)&0xFFFFFFFF));
 
 	if ((ret=writefd(f,b,8)) != 8) {
-		fprintf(FERROR,"write_longint failed : %s\n",
+		rprintf(FERROR,"write_longint failed : %s\n",
 			ret==-1?strerror(errno):"EOF");
 		exit_cleanup(1);
 	}
 	total_written += 8;
 }
 
 void write_buf(int f,char *buf,int len)
 {
   int ret;
   if ((ret=writefd(f,buf,len)) != len) {
-    fprintf(FERROR,"write_buf failed : %s\n",
+    rprintf(FERROR,"write_buf failed : %s\n",
 	    ret==-1?strerror(errno):"EOF");
     exit_cleanup(1);
   }
   total_written += len;
 }
 
+/* write a string to the connection */
+void write_sbuf(int f,char *buf)
+{
+	write_buf(f, buf, strlen(buf));
+}
+
 
 void write_byte(int f,unsigned char c)
 {
-  write_buf(f,(char *)&c,1);
+	write_buf(f,(char *)&c,1);
 }
 
 void write_flush(int f)
 {
 }
 
 
+int read_line(int f, char *buf, int maxlen)
+{
+	while (maxlen) {
+		read_buf(f, buf, 1);
+		if (buf[0] == '\n') {
+			buf[0] = 0;
+			break;
+		}
+		if (buf[0] != '\r') {
+			buf++;
+			maxlen--;
+		}
+	}
+	if (maxlen == 0) {
+		*buf = 0;
+		return 0;
+	}
+	return 1;
+}
+
+
+void io_printf(int fd, const char *format, ...)
+{
+	va_list ap;  
+	char buf[1024];
+	int len;
+	
+	va_start(ap, format);
+
+#if HAVE_VSNPRINTF
+	len = vsnprintf(buf, sizeof(buf)-1, format, ap);
+#else
+	vsprintf(buf, format, ap);
+	len = strlen(buf);
+#endif
+	va_end(ap);
+
+	if (len < 0) exit_cleanup(1);
+
+	write_sbuf(fd, buf);
+}
