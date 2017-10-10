 	const char *config_name;
 	daemon_service_fn fn;
 	int enabled;
 	int overridable;
 };
 
-static struct daemon_service *service_looking_at;
-static int service_enabled;
-
-static int git_daemon_config(const char *var, const char *value, void *cb)
-{
-	const char *service;
-
-	if (skip_prefix(var, "daemon.", &service) &&
-	    !strcmp(service, service_looking_at->config_name)) {
-		service_enabled = git_config_bool(var, value);
-		return 0;
-	}
-
-	/* we are not interested in parsing any other configuration here */
-	return 0;
-}
-
 static int daemon_error(const char *dir, const char *msg)
 {
 	if (!informative_errors)
 		msg = "access denied or repository not exported";
 	packet_write(1, "ERR %s: %s", msg, dir);
 	return -1;
 }
 
 static const char *access_hook;
 
 static int run_access_hook(struct daemon_service *service, const char *dir, const char *path)
 {
-	struct child_process child;
+	struct child_process child = CHILD_PROCESS_INIT;
 	struct strbuf buf = STRBUF_INIT;
 	const char *argv[8];
 	const char **arg = argv;
 	char *eol;
 	int seen_errors = 0;
 
