 static int sequencer_in_use;
 static int use_editor = 1, include_status = 1;
 static int show_ignored_in_status, have_option_m;
 static const char *only_include_assumed;
 static struct strbuf message = STRBUF_INIT;
 
-static enum status_format {
-	STATUS_FORMAT_NONE = 0,
-	STATUS_FORMAT_LONG,
-	STATUS_FORMAT_SHORT,
-	STATUS_FORMAT_PORCELAIN,
+static enum wt_status_format status_format = STATUS_FORMAT_UNSPECIFIED;
 
-	STATUS_FORMAT_UNSPECIFIED
-} status_format = STATUS_FORMAT_UNSPECIFIED;
+static int opt_parse_porcelain(const struct option *opt, const char *arg, int unset)
+{
+	enum wt_status_format *value = (enum wt_status_format *)opt->value;
+	if (unset)
+		*value = STATUS_FORMAT_NONE;
+	else if (!arg)
+		*value = STATUS_FORMAT_PORCELAIN;
+	else if (!strcmp(arg, "v1") || !strcmp(arg, "1"))
+		*value = STATUS_FORMAT_PORCELAIN;
+	else if (!strcmp(arg, "v2") || !strcmp(arg, "2"))
+		*value = STATUS_FORMAT_PORCELAIN_V2;
+	else
+		die("unsupported porcelain version '%s'", arg);
+
+	return 0;
+}
 
 static int opt_parse_m(const struct option *opt, const char *arg, int unset)
 {
 	struct strbuf *buf = opt->value;
 	if (unset) {
 		have_option_m = 0;
