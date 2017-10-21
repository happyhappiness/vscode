     exit_cleanup(1);
   }
   total_read += 4;
   return IVAL(b,0);
 }
 
+int64 read_longint(int f)
+{
+	extern int remote_version;
+	int64 ret;
+	char b[8];
+	ret = read_int(f);
+
+	if (ret != -1) return ret;
+
+#ifndef HAVE_LONGLONG
+	fprintf(FERROR,"Integer overflow - attempted 64 bit offset\n");
+	exit_cleanup(1);
+#else
+	if (remote_version >= 16) {
+		if ((ret=readfd(f,b,8)) != 8) {
+			if (verbose > 1) 
+				fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
+					getpid(),8,ret==-1?strerror(errno):"EOF");
+			exit_cleanup(1);
+		}
+		total_read += 8;
+		ret = IVAL(b,0) | (((int64)IVAL(b,4))<<32);
+	}
+#endif
+
+	return ret;
+}
+
 void read_buf(int f,char *buf,int len)
 {
   int ret;
   if ((ret=readfd(f,buf,len)) != len) {
     if (verbose > 1) 
       fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
