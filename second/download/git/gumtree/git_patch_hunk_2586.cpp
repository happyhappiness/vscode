 	printf("password=%s\n", c->password);
 }
 
 static void print_line(struct strbuf *buf)
 {
 	strbuf_addch(buf, '\n');
-	write_or_die(credential_lock.fd, buf->buf, buf->len);
+	write_or_die(get_lock_file_fd(&credential_lock), buf->buf, buf->len);
 }
 
 static void rewrite_credential_file(const char *fn, struct credential *c,
 				    struct strbuf *extra)
 {
 	if (hold_lock_file_for_update(&credential_lock, fn, 0) < 0)
