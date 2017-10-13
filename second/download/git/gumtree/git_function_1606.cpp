static void git_imap_config(void)
{
	const char *val = NULL;

	git_config_get_bool("imap.sslverify", &server.ssl_verify);
	git_config_get_bool("imap.preformattedhtml", &server.use_html);
	git_config_get_string("imap.folder", &server.folder);

	if (!git_config_get_value("imap.host", &val)) {
		if (!val) {
			git_die_config("imap.host", "Missing value for 'imap.host'");
		} else {
			if (starts_with(val, "imap:"))
				val += 5;
			else if (starts_with(val, "imaps:")) {
				val += 6;
				server.use_ssl = 1;
			}
			if (starts_with(val, "//"))
				val += 2;
			server.host = xstrdup(val);
		}
	}

	git_config_get_string("imap.user", &server.user);
	git_config_get_string("imap.pass", &server.pass);
	git_config_get_int("imap.port", &server.port);
	git_config_get_string("imap.tunnel", &server.tunnel);
	git_config_get_string("imap.authmethod", &server.auth_method);
}