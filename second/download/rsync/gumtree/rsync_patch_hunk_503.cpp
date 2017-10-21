 	}
 	globfree(&globbuf);
 	(*argc) += i;
 #endif
 }
 
+void glob_expand(char *base, char **argv, int *argc, int maxargs)
+{
+	char *s = argv[*argc];
+	char *p, *q;
+
+	if (!s || !*s) return;
+
+	if (strncmp(s, base, strlen(base)) == 0) {
+		s += strlen(base);
+	}
+
+	s = strdup(s);
+	if (!s) out_of_memory("glob_expand");
+
+	q = s;
+	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
+		if (p != q && *(p-1) == ' ' && p[strlen(base)] == '/') {
+			/* split it at this point */
+			*(p-1) = 0;
+			glob_expand_one(q, argv, argc, maxargs);
+			q = p+strlen(base)+1;
+		} else {
+			q++;
+		}
+	}
+
+	if (*q && (*argc < maxargs)) glob_expand_one(q, argv, argc, maxargs);
+
+	free(s);
+}
 
 /*******************************************************************
   convert a string to lower case
 ********************************************************************/
 void strlower(char *s)
 {
 	while (*s) {
 		if (isupper(*s)) *s = tolower(*s);
 		s++;
 	}
 }
+
+/* this is like vsnprintf but the 'n' limit does not include
+   the terminating null. So if you have a 1024 byte buffer then
+   pass 1023 for n */
+int vslprintf(char *str, int n, const char *format, va_list ap)
+{
+#ifdef HAVE_VSNPRINTF
+	int ret = vsnprintf(str, n, format, ap);
+	if (ret > n || ret < 0) {
+		str[n] = 0;
+		return -1;
+	}
+	str[ret] = 0;
+	return ret;
+#else
+	static char *buf;
+	static int len=MAXPATHLEN*8;
+	int ret;
+
+	/* this code is NOT a proper vsnprintf() implementation. It
+	   relies on the fact that all calls to slprintf() in rsync
+	   pass strings which have already been checked to be less
+	   than MAXPATHLEN in length and never more than 2 strings are
+	   concatenated. This means the above buffer is absolutely
+	   ample and can never be overflowed.
+
+	   In the future we would like to replace this with a proper
+	   vsnprintf() implementation but right now we need a solution
+	   that is secure and portable. This is it.  */
+
+	if (!buf) {
+		buf = malloc(len);
+		if (!buf) {
+			/* can't call debug or we would recurse */
+			exit(1);
+		}
+	}
+
+	ret = vsprintf(buf, format, ap);
+
+	if (ret < 0) {
+		str[0] = 0;
+		return -1;
+	}
+
+	if (ret < n) {
+		n = ret;
+	} else if (ret > n) {
+		ret = -1;
+	}
+
+	buf[n] = 0;
+	
+	memcpy(str, buf, n+1);
+
+	return ret;
+#endif
+}
+
+
+/* like snprintf but always null terminates */
+int slprintf(char *str, int n, char *format, ...)
+{
+	va_list ap;  
+	int ret;
+
+	va_start(ap, format);
+	ret = vslprintf(str,n,format,ap);
+	va_end(ap);
+	return ret;
+}
