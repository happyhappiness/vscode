 	return 1;
 }
 
 NORETURN
 static void die_bad_number(const char *name, const char *value)
 {
-	const char *reason = errno == ERANGE ?
-			     "out of range" :
-			     "invalid unit";
+	const char * error_type = (errno == ERANGE)? _("out of range"):_("invalid unit");
+
 	if (!value)
 		value = "";
 
-	if (cf && cf->origin_type && cf->name)
-		die(_("bad numeric config value '%s' for '%s' in %s %s: %s"),
-		    value, name, cf->origin_type, cf->name, reason);
-	die(_("bad numeric config value '%s' for '%s': %s"), value, name, reason);
+	if (!(cf && cf->name))
+		die(_("bad numeric config value '%s' for '%s': %s"),
+		    value, name, error_type);
+
+	switch (cf->origin_type) {
+	case CONFIG_ORIGIN_BLOB:
+		die(_("bad numeric config value '%s' for '%s' in blob %s: %s"),
+		    value, name, cf->name, error_type);
+	case CONFIG_ORIGIN_FILE:
+		die(_("bad numeric config value '%s' for '%s' in file %s: %s"),
+		    value, name, cf->name, error_type);
+	case CONFIG_ORIGIN_STDIN:
+		die(_("bad numeric config value '%s' for '%s' in standard input: %s"),
+		    value, name, error_type);
+	case CONFIG_ORIGIN_SUBMODULE_BLOB:
+		die(_("bad numeric config value '%s' for '%s' in submodule-blob %s: %s"),
+		    value, name, cf->name, error_type);
+	case CONFIG_ORIGIN_CMDLINE:
+		die(_("bad numeric config value '%s' for '%s' in command line %s: %s"),
+		    value, name, cf->name, error_type);
+	default:
+		die(_("bad numeric config value '%s' for '%s' in %s: %s"),
+		    value, name, cf->name, error_type);
+	}
 }
 
 int git_config_int(const char *name, const char *value)
 {
 	int ret;
 	if (!git_parse_int(value, &ret))
