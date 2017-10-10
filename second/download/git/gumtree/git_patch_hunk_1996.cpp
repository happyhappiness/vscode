 	git_config_get_string("imap.pass", &server.pass);
 	git_config_get_int("imap.port", &server.port);
 	git_config_get_string("imap.tunnel", &server.tunnel);
 	git_config_get_string("imap.authmethod", &server.auth_method);
 }
 
-int main(int argc, char **argv)
+static int append_msgs_to_imap(struct imap_server_conf *server,
+			       struct strbuf* all_msgs, int total)
 {
-	struct strbuf all_msgs = STRBUF_INIT;
 	struct strbuf msg = STRBUF_INIT;
 	struct imap_store *ctx = NULL;
 	int ofs = 0;
 	int r;
-	int total, n = 0;
+	int n = 0;
+
+	ctx = imap_open_store(server, server->folder);
+	if (!ctx) {
+		fprintf(stderr, "failed to open store\n");
+		return 1;
+	}
+	ctx->name = server->folder;
+
+	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
+	while (1) {
+		unsigned percent = n * 100 / total;
+
+		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);
+
+		if (!split_msg(all_msgs, &msg, &ofs))
+			break;
+		if (server->use_html)
+			wrap_in_html(&msg);
+		r = imap_store_msg(ctx, &msg);
+		if (r != DRV_OK)
+			break;
+		n++;
+	}
+	fprintf(stderr, "\n");
+
+	imap_close_store(ctx);
+
+	return 0;
+}
+
+#ifdef USE_CURL_FOR_IMAP_SEND
+static CURL *setup_curl(struct imap_server_conf *srvc)
+{
+	CURL *curl;
+	struct strbuf path = STRBUF_INIT;
+
+	if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
+		die("curl_global_init failed");
+
+	curl = curl_easy_init();
+
+	if (!curl)
+		die("curl_easy_init failed");
+
+	curl_easy_setopt(curl, CURLOPT_USERNAME, server.user);
+	curl_easy_setopt(curl, CURLOPT_PASSWORD, server.pass);
+
+	strbuf_addstr(&path, server.host);
+	if (!path.len || path.buf[path.len - 1] != '/')
+		strbuf_addch(&path, '/');
+	strbuf_addstr(&path, server.folder);
+
+	curl_easy_setopt(curl, CURLOPT_URL, path.buf);
+	strbuf_release(&path);
+	curl_easy_setopt(curl, CURLOPT_PORT, server.port);
+
+	if (server.auth_method) {
+		struct strbuf auth = STRBUF_INIT;
+		strbuf_addstr(&auth, "AUTH=");
+		strbuf_addstr(&auth, server.auth_method);
+		curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, auth.buf);
+		strbuf_release(&auth);
+	}
+
+	if (!server.use_ssl)
+		curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_TRY);
+
+	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, server.ssl_verify);
+	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, server.ssl_verify);
+
+	curl_easy_setopt(curl, CURLOPT_READFUNCTION, fread_buffer);
+
+	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
+
+	if (0 < verbosity || getenv("GIT_CURL_VERBOSE"))
+		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
+
+	return curl;
+}
+
+static int curl_append_msgs_to_imap(struct imap_server_conf *server,
+				    struct strbuf* all_msgs, int total) {
+	int ofs = 0;
+	int n = 0;
+	struct buffer msgbuf = { STRBUF_INIT, 0 };
+	CURL *curl;
+	CURLcode res = CURLE_OK;
+
+	curl = setup_curl(server);
+	curl_easy_setopt(curl, CURLOPT_READDATA, &msgbuf);
+
+	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
+	while (1) {
+		unsigned percent = n * 100 / total;
+		int prev_len;
+
+		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);
+
+		prev_len = msgbuf.buf.len;
+		if (!split_msg(all_msgs, &msgbuf.buf, &ofs))
+			break;
+		if (server->use_html)
+			wrap_in_html(&msgbuf.buf);
+		lf_to_crlf(&msgbuf.buf);
+
+		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
+				 (curl_off_t)(msgbuf.buf.len-prev_len));
+
+		res = curl_easy_perform(curl);
+
+		if(res != CURLE_OK) {
+			fprintf(stderr, "curl_easy_perform() failed: %s\n",
+					curl_easy_strerror(res));
+			break;
+		}
+
+		n++;
+	}
+	fprintf(stderr, "\n");
+
+	curl_easy_cleanup(curl);
+	curl_global_cleanup();
+
+	return 0;
+}
+#endif
+
+int main(int argc, char **argv)
+{
+	struct strbuf all_msgs = STRBUF_INIT;
+	int total;
 	int nongit_ok;
 
 	git_extract_argv0_path(argv[0]);
 
 	git_setup_gettext();
 
-	if (argc != 1)
-		usage(imap_send_usage);
-
 	setup_git_directory_gently(&nongit_ok);
 	git_imap_config();
 
+	argc = parse_options(argc, (const char **)argv, "", imap_send_options, imap_send_usage, 0);
+
+	if (argc)
+		usage_with_options(imap_send_usage, imap_send_options);
+
+#ifndef USE_CURL_FOR_IMAP_SEND
+	if (use_curl) {
+		warning("--use-curl not supported in this build");
+		use_curl = 0;
+	}
+#endif
+
 	if (!server.port)
 		server.port = server.use_ssl ? 993 : 143;
 
 	if (!server.folder) {
 		fprintf(stderr, "no imap store specified\n");
 		return 1;
