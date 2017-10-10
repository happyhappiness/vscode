
	if (strcmp(var, "receive.keepalive") == 0) {
		keepalive_in_sec = git_config_int(var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}

static void show_ref(const char *path, const unsigned char *sha1)
{
	if (sent_capabilities) {
		packet_write(1, "%s %s\n", sha1_to_hex(sha1), path);
	} else {
		struct strbuf cap = STRBUF_INIT;

		strbuf_addstr(&cap,
			      "report-status delete-refs side-band-64k quiet");
		if (advertise_atomic_push)
