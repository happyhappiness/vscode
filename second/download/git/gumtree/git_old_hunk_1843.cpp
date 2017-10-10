
	strbuf_add(msg, data, len);
	*ofs += len;
	return 1;
}

static char *imap_folder;

static int git_imap_config(const char *key, const char *val, void *cb)
{
	if (!skip_prefix(key, "imap.", &key))
		return 0;

	/* check booleans first, and barf on others */
	if (!strcmp("sslverify", key))
		server.ssl_verify = git_config_bool(key, val);
	else if (!strcmp("preformattedhtml", key))
		server.use_html = git_config_bool(key, val);
	else if (!val)
		return config_error_nonbool(key);

	if (!strcmp("folder", key)) {
		imap_folder = xstrdup(val);
	} else if (!strcmp("host", key)) {
		if (starts_with(val, "imap:"))
			val += 5;
		else if (starts_with(val, "imaps:")) {
			val += 6;
			server.use_ssl = 1;
		}
		if (starts_with(val, "//"))
			val += 2;
		server.host = xstrdup(val);
	} else if (!strcmp("user", key))
		server.user = xstrdup(val);
	else if (!strcmp("pass", key))
		server.pass = xstrdup(val);
	else if (!strcmp("port", key))
		server.port = git_config_int(key, val);
	else if (!strcmp("tunnel", key))
		server.tunnel = xstrdup(val);
	else if (!strcmp("authmethod", key))
		server.auth_method = xstrdup(val);

	return 0;
}

int main(int argc, char **argv)
{
	struct strbuf all_msgs = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
