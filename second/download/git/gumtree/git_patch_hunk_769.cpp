 		}
 	}
 
 	return enabled ? &allowed : NULL;
 }
 
-int is_transport_allowed(const char *type)
+enum protocol_allow_config {
+	PROTOCOL_ALLOW_NEVER = 0,
+	PROTOCOL_ALLOW_USER_ONLY,
+	PROTOCOL_ALLOW_ALWAYS
+};
+
+static enum protocol_allow_config parse_protocol_config(const char *key,
+							const char *value)
 {
-	const struct string_list *allowed = protocol_whitelist();
-	return !allowed || string_list_has_string(allowed, type);
+	if (!strcasecmp(value, "always"))
+		return PROTOCOL_ALLOW_ALWAYS;
+	else if (!strcasecmp(value, "never"))
+		return PROTOCOL_ALLOW_NEVER;
+	else if (!strcasecmp(value, "user"))
+		return PROTOCOL_ALLOW_USER_ONLY;
+
+	die("unknown value for config '%s': %s", key, value);
+}
+
+static enum protocol_allow_config get_protocol_config(const char *type)
+{
+	char *key = xstrfmt("protocol.%s.allow", type);
+	char *value;
+
+	/* first check the per-protocol config */
+	if (!git_config_get_string(key, &value)) {
+		enum protocol_allow_config ret =
+			parse_protocol_config(key, value);
+		free(key);
+		free(value);
+		return ret;
+	}
+	free(key);
+
+	/* if defined, fallback to user-defined default for unknown protocols */
+	if (!git_config_get_string("protocol.allow", &value)) {
+		enum protocol_allow_config ret =
+			parse_protocol_config("protocol.allow", value);
+		free(value);
+		return ret;
+	}
+
+	/* fallback to built-in defaults */
+	/* known safe */
+	if (!strcmp(type, "http") ||
+	    !strcmp(type, "https") ||
+	    !strcmp(type, "git") ||
+	    !strcmp(type, "ssh") ||
+	    !strcmp(type, "file"))
+		return PROTOCOL_ALLOW_ALWAYS;
+
+	/* known scary; err on the side of caution */
+	if (!strcmp(type, "ext"))
+		return PROTOCOL_ALLOW_NEVER;
+
+	/* unknown; by default let them be used only directly by the user */
+	return PROTOCOL_ALLOW_USER_ONLY;
+}
+
+int is_transport_allowed(const char *type, int from_user)
+{
+	const struct string_list *whitelist = protocol_whitelist();
+	if (whitelist)
+		return string_list_has_string(whitelist, type);
+
+	switch (get_protocol_config(type)) {
+	case PROTOCOL_ALLOW_ALWAYS:
+		return 1;
+	case PROTOCOL_ALLOW_NEVER:
+		return 0;
+	case PROTOCOL_ALLOW_USER_ONLY:
+		if (from_user < 0)
+			from_user = git_env_bool("GIT_PROTOCOL_FROM_USER", 1);
+		return from_user;
+	}
+
+	die("BUG: invalid protocol_allow_config type");
 }
 
 void transport_check_allowed(const char *type)
 {
-	if (!is_transport_allowed(type))
+	if (!is_transport_allowed(type, -1))
 		die("transport '%s' not allowed", type);
 }
 
-int transport_restrict_protocols(void)
-{
-	return !!protocol_whitelist();
-}
-
 struct transport *transport_get(struct remote *remote, const char *url)
 {
 	const char *helper;
 	struct transport *ret = xcalloc(1, sizeof(*ret));
 
 	ret->progress = isatty(2);
