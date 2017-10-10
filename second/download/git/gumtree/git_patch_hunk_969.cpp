 
 	ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
 	opts->xopts[opts->xopts_nr++] = xstrdup(arg);
 	return 0;
 }
 
+static int option_parse_m(const struct option *opt,
+			  const char *arg, int unset)
+{
+	struct replay_opts *replay = opt->value;
+	char *end;
+
+	if (unset) {
+		replay->mainline = 0;
+		return 0;
+	}
+
+	replay->mainline = strtol(arg, &end, 10);
+	if (*end || replay->mainline <= 0)
+		return opterror(opt, "expects a number greater than zero", 0);
+
+	return 0;
+}
+
 LAST_ARG_MUST_BE_NULL
 static void verify_opt_compatible(const char *me, const char *base_opt, ...)
 {
 	const char *this_opt;
 	va_list ap;
 
