 
 static int external_specification_len(const char *url)
 {
 	return strchr(url, ':') - url;
 }
 
-static const struct string_list *protocol_whitelist(void)
-{
-	static int enabled = -1;
-	static struct string_list allowed = STRING_LIST_INIT_DUP;
-
-	if (enabled < 0) {
-		const char *v = getenv("GIT_ALLOW_PROTOCOL");
-		if (v) {
-			string_list_split(&allowed, v, ':', -1);
-			string_list_sort(&allowed);
-			enabled = 1;
-		} else {
-			enabled = 0;
-		}
-	}
-
-	return enabled ? &allowed : NULL;
-}
-
-int is_transport_allowed(const char *type)
-{
-	const struct string_list *allowed = protocol_whitelist();
-	return !allowed || string_list_has_string(allowed, type);
-}
-
-void transport_check_allowed(const char *type)
-{
-	if (!is_transport_allowed(type))
-		die("transport '%s' not allowed", type);
-}
-
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
