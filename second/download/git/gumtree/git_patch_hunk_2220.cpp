 {
 	remove_pidfile();
 	sigchain_pop(signo);
 	raise(signo);
 }
 
+static void git_config_date_string(const char *key, const char **output)
+{
+	if (git_config_get_string_const(key, output))
+		return;
+	if (strcmp(*output, "now")) {
+		unsigned long now = approxidate("now");
+		if (approxidate(*output) >= now)
+			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
+	}
+}
+
 static void gc_config(void)
 {
 	const char *value;
 
 	if (!git_config_get_value("gc.packrefs", &value)) {
 		if (value && !strcmp(value, "notbare"))
