 
 	strbuf_add(msg, data, len);
 	*ofs += len;
 	return 1;
 }
 
-static char *imap_folder;
-
-static int git_imap_config(const char *key, const char *val, void *cb)
+static void git_imap_config(void)
 {
-	if (!skip_prefix(key, "imap.", &key))
-		return 0;
+	const char *val = NULL;
 
-	/* check booleans first, and barf on others */
-	if (!strcmp("sslverify", key))
-		server.ssl_verify = git_config_bool(key, val);
-	else if (!strcmp("preformattedhtml", key))
-		server.use_html = git_config_bool(key, val);
-	else if (!val)
-		return config_error_nonbool(key);
-
-	if (!strcmp("folder", key)) {
-		imap_folder = xstrdup(val);
-	} else if (!strcmp("host", key)) {
-		if (starts_with(val, "imap:"))
-			val += 5;
-		else if (starts_with(val, "imaps:")) {
-			val += 6;
-			server.use_ssl = 1;
-		}
-		if (starts_with(val, "//"))
-			val += 2;
-		server.host = xstrdup(val);
-	} else if (!strcmp("user", key))
-		server.user = xstrdup(val);
-	else if (!strcmp("pass", key))
-		server.pass = xstrdup(val);
-	else if (!strcmp("port", key))
-		server.port = git_config_int(key, val);
-	else if (!strcmp("tunnel", key))
-		server.tunnel = xstrdup(val);
-	else if (!strcmp("authmethod", key))
-		server.auth_method = xstrdup(val);
+	git_config_get_bool("imap.sslverify", &server.ssl_verify);
+	git_config_get_bool("imap.preformattedhtml", &server.use_html);
+	git_config_get_string("imap.folder", &server.folder);
 
-	return 0;
+	if (!git_config_get_value("imap.host", &val)) {
+		if (!val) {
+			git_die_config("imap.host", "Missing value for 'imap.host'");
+		} else {
+			if (starts_with(val, "imap:"))
+				val += 5;
+			else if (starts_with(val, "imaps:")) {
+				val += 6;
+				server.use_ssl = 1;
+			}
+			if (starts_with(val, "//"))
+				val += 2;
+			server.host = xstrdup(val);
+		}
+	}
+
+	git_config_get_string("imap.user", &server.user);
+	git_config_get_string("imap.pass", &server.pass);
+	git_config_get_int("imap.port", &server.port);
+	git_config_get_string("imap.tunnel", &server.tunnel);
+	git_config_get_string("imap.authmethod", &server.auth_method);
 }
 
 int main(int argc, char **argv)
 {
 	struct strbuf all_msgs = STRBUF_INIT;
 	struct strbuf msg = STRBUF_INIT;
