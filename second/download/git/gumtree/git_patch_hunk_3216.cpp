 				http_auth.username, http_auth.password);
 		curl_easy_setopt(result, CURLOPT_USERPWD, up.buf);
 	}
 #endif
 }
 
+/* *var must be free-able */
+static void var_override(const char **var, char *value)
+{
+	if (value) {
+		free((void *)*var);
+		*var = xstrdup(value);
+	}
+}
+
+static void set_proxyauth_name_password(CURL *result)
+{
+#if LIBCURL_VERSION_NUM >= 0x071301
+		curl_easy_setopt(result, CURLOPT_PROXYUSERNAME,
+			proxy_auth.username);
+		curl_easy_setopt(result, CURLOPT_PROXYPASSWORD,
+			proxy_auth.password);
+#else
+		struct strbuf s = STRBUF_INIT;
+
+		strbuf_addstr_urlencode(&s, proxy_auth.username, 1);
+		strbuf_addch(&s, ':');
+		strbuf_addstr_urlencode(&s, proxy_auth.password, 1);
+		curl_proxyuserpwd = strbuf_detach(&s, NULL);
+		curl_easy_setopt(result, CURLOPT_PROXYUSERPWD, curl_proxyuserpwd);
+#endif
+}
+
+static void init_curl_proxy_auth(CURL *result)
+{
+	if (proxy_auth.username) {
+		if (!proxy_auth.password)
+			credential_fill(&proxy_auth);
+		set_proxyauth_name_password(result);
+	}
+
+	var_override(&http_proxy_authmethod, getenv("GIT_HTTP_PROXY_AUTHMETHOD"));
+
+#if LIBCURL_VERSION_NUM >= 0x070a07 /* CURLOPT_PROXYAUTH and CURLAUTH_ANY */
+	if (http_proxy_authmethod) {
+		int i;
+		for (i = 0; i < ARRAY_SIZE(proxy_authmethods); i++) {
+			if (!strcmp(http_proxy_authmethod, proxy_authmethods[i].name)) {
+				curl_easy_setopt(result, CURLOPT_PROXYAUTH,
+						proxy_authmethods[i].curlauth_param);
+				break;
+			}
+		}
+		if (i == ARRAY_SIZE(proxy_authmethods)) {
+			warning("unsupported proxy authentication method %s: using anyauth",
+					http_proxy_authmethod);
+			curl_easy_setopt(result, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
+		}
+	}
+	else
+		curl_easy_setopt(result, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
+#endif
+}
+
 static int has_cert_password(void)
 {
 	if (ssl_cert == NULL || ssl_cert_password_required != 1)
 		return 0;
 	if (!cert_auth.password) {
 		cert_auth.protocol = xstrdup("cert");
