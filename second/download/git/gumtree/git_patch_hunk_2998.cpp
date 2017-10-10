 
 static inline void ferr_puts(const char *s, FILE *fp, int *err)
 {
 	ferr_write(s, strlen(s), fp, err);
 }
 
-struct rerere_io {
-	int (*getline)(struct strbuf *, struct rerere_io *);
-	FILE *output;
-	int wrerror;
-	/* some more stuff */
-};
-
 static void rerere_io_putstr(const char *str, struct rerere_io *io)
 {
 	if (io->output)
 		ferr_puts(str, io->output, &io->wrerror);
 }
 
+/*
+ * Write a conflict marker to io->output (if defined).
+ */
 static void rerere_io_putconflict(int ch, int size, struct rerere_io *io)
 {
 	char buf[64];
 
 	while (size) {
-		if (size < sizeof(buf) - 2) {
+		if (size <= sizeof(buf) - 2) {
 			memset(buf, ch, size);
 			buf[size] = '\n';
 			buf[size + 1] = '\0';
 			size = 0;
 		} else {
 			int sz = sizeof(buf) - 1;
+
+			/*
+			 * Make sure we will not write everything out
+			 * in this round by leaving at least 1 byte
+			 * for the next round, giving the next round
+			 * a chance to add the terminating LF.  Yuck.
+			 */
 			if (size <= sz)
 				sz -= (sz - size) + 1;
 			memset(buf, ch, sz);
 			buf[sz] = '\0';
 			size -= sz;
 		}
