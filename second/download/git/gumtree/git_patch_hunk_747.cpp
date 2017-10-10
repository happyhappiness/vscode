 	if (!error_flag)
 		return error(_("invalid value for %s: %s"), key, value);
 
 	return 0;
 }
 
+static void read_strategy_opts(struct replay_opts *opts, struct strbuf *buf)
+{
+	int i;
+
+	strbuf_reset(buf);
+	if (!read_oneliner(buf, rebase_path_strategy(), 0))
+		return;
+	opts->strategy = strbuf_detach(buf, NULL);
+	if (!read_oneliner(buf, rebase_path_strategy_opts(), 0))
+		return;
+
+	opts->xopts_nr = split_cmdline(buf->buf, (const char ***)&opts->xopts);
+	for (i = 0; i < opts->xopts_nr; i++) {
+		const char *arg = opts->xopts[i];
+
+		skip_prefix(arg, "--", &arg);
+		opts->xopts[i] = xstrdup(arg);
+	}
+}
+
 static int read_populate_opts(struct replay_opts *opts)
 {
 	if (is_rebase_i(opts)) {
 		struct strbuf buf = STRBUF_INIT;
 
 		if (read_oneliner(&buf, rebase_path_gpg_sign_opt(), 1)) {
