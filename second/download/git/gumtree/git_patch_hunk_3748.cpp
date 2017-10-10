 	{"GET", "/objects/pack/pack-[0-9a-f]{40}\\.idx$", get_idx_file},
 
 	{"POST", "/git-upload-pack$", service_rpc},
 	{"POST", "/git-receive-pack$", service_rpc}
 };
 
+static int bad_request(struct strbuf *hdr, const struct service_cmd *c)
+{
+	const char *proto = getenv("SERVER_PROTOCOL");
+
+	if (proto && !strcmp(proto, "HTTP/1.1")) {
+		http_status(hdr, 405, "Method Not Allowed");
+		hdr_str(hdr, "Allow",
+			!strcmp(c->method, "GET") ? "GET, HEAD" : c->method);
+	} else
+		http_status(hdr, 400, "Bad Request");
+	hdr_nocache(hdr);
+	end_headers(hdr);
+	return 0;
+}
+
 int cmd_main(int argc, const char **argv)
 {
 	char *method = getenv("REQUEST_METHOD");
 	char *dir;
 	struct service_cmd *cmd = NULL;
 	char *cmd_arg = NULL;
 	int i;
+	struct strbuf hdr = STRBUF_INIT;
 
 	set_die_routine(die_webcgi);
 	set_die_is_recursing_routine(die_webcgi_recursing);
 
 	if (!method)
 		die("No REQUEST_METHOD from server");
