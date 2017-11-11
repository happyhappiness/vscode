static int set_option(const char *name, const char *value)
{
	if (!strcmp(name, "verbosity")) {
		char *end;
		int v = strtol(value, &end, 10);
		if (value == end || *end)
			return -1;
		options.verbosity = v;
		return 0;
	}
	else if (!strcmp(name, "progress")) {
		if (!strcmp(value, "true"))
			options.progress = 1;
		else if (!strcmp(value, "false"))
			options.progress = 0;
		else
			return -1;
		return 0;
	}
	else if (!strcmp(name, "depth")) {
		char *end;
		unsigned long v = strtoul(value, &end, 10);
		if (value == end || *end)
			return -1;
		options.depth = v;
		return 0;
	}
	else if (!strcmp(name, "deepen-since")) {
		options.deepen_since = xstrdup(value);
		return 0;
	}
	else if (!strcmp(name, "deepen-not")) {
		string_list_append(&options.deepen_not, value);
		return 0;
	}
	else if (!strcmp(name, "deepen-relative")) {
		if (!strcmp(value, "true"))
			options.deepen_relative = 1;
		else if (!strcmp(value, "false"))
			options.deepen_relative = 0;
		else
			return -1;
		return 0;
	}
	else if (!strcmp(name, "followtags")) {
		if (!strcmp(value, "true"))
			options.followtags = 1;
		else if (!strcmp(value, "false"))
			options.followtags = 0;
		else
			return -1;
		return 0;
	}
	else if (!strcmp(name, "dry-run")) {
		if (!strcmp(value, "true"))
			options.dry_run = 1;
		else if (!strcmp(value, "false"))
			options.dry_run = 0;
		else
			return -1;
		return 0;
	}
	else if (!strcmp(name, "check-connectivity")) {
		if (!strcmp(value, "true"))
			options.check_self_contained_and_connected = 1;
		else if (!strcmp(value, "false"))
			options.check_self_contained_and_connected = 0;
		else
			return -1;
		return 0;
	}
	else if (!strcmp(name, "cas")) {
		struct strbuf val = STRBUF_INIT;
		strbuf_addf(&val, "--" CAS_OPT_NAME "=%s", value);
		string_list_append(&cas_options, val.buf);
		strbuf_release(&val);
		return 0;
	} else if (!strcmp(name, "cloning")) {
		if (!strcmp(value, "true"))
			options.cloning = 1;
		else if (!strcmp(value, "false"))
			options.cloning = 0;
		else
			return -1;
		return 0;
	} else if (!strcmp(name, "update-shallow")) {
		if (!strcmp(value, "true"))
			options.update_shallow = 1;
		else if (!strcmp(value, "false"))
			options.update_shallow = 0;
		else
			return -1;
		return 0;
	} else if (!strcmp(name, "pushcert")) {
		if (!strcmp(value, "true"))
			options.push_cert = SEND_PACK_PUSH_CERT_ALWAYS;
		else if (!strcmp(value, "false"))
			options.push_cert = SEND_PACK_PUSH_CERT_NEVER;
		else if (!strcmp(value, "if-asked"))
			options.push_cert = SEND_PACK_PUSH_CERT_IF_ASKED;
		else
			return -1;
		return 0;

#if LIBCURL_VERSION_NUM >= 0x070a08
	} else if (!strcmp(name, "family")) {
		if (!strcmp(value, "ipv4"))
			git_curl_ipresolve = CURL_IPRESOLVE_V4;
		else if (!strcmp(value, "ipv6"))
			git_curl_ipresolve = CURL_IPRESOLVE_V6;
		else if (!strcmp(value, "all"))
			git_curl_ipresolve = CURL_IPRESOLVE_WHATEVER;
		else
			return -1;
		return 0;
#endif /* LIBCURL_VERSION_NUM >= 0x070a08 */
	} else {
		return 1 /* unsupported */;
	}
}