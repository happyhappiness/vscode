 static int read_request(FILE *fh, struct credential *c,
 			struct strbuf *action, int *timeout) {
 	static struct strbuf item = STRBUF_INIT;
 	const char *p;
 
 	strbuf_getline(&item, fh, '\n');
-	p = skip_prefix(item.buf, "action=");
-	if (!p)
+	if (!skip_prefix(item.buf, "action=", &p))
 		return error("client sent bogus action line: %s", item.buf);
 	strbuf_addstr(action, p);
 
 	strbuf_getline(&item, fh, '\n');
-	p = skip_prefix(item.buf, "timeout=");
-	if (!p)
+	if (!skip_prefix(item.buf, "timeout=", &p))
 		return error("client sent bogus timeout line: %s", item.buf);
 	*timeout = atoi(p);
 
 	if (credential_read(c, fh) < 0)
 		return -1;
 	return 0;
