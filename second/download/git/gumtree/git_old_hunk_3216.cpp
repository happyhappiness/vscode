				http_auth.username, http_auth.password);
		curl_easy_setopt(result, CURLOPT_USERPWD, up.buf);
	}
#endif
}

static int has_cert_password(void)
{
	if (ssl_cert == NULL || ssl_cert_password_required != 1)
		return 0;
	if (!cert_auth.password) {
		cert_auth.protocol = xstrdup("cert");
