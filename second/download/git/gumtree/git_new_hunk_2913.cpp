		*strlen_c = strlen_chars;

	return ret;
}


void probe_utf8_pathname_composition(void)
{
	struct strbuf path = STRBUF_INIT;
	static const char *auml_nfc = "\xc3\xa4";
	static const char *auml_nfd = "\x61\xcc\x88";
	int output_fd;
	if (precomposed_unicode != -1)
		return; /* We found it defined in the global config, respect it */
	git_path_buf(&path, "%s", auml_nfc);
	output_fd = open(path.buf, O_CREAT|O_EXCL|O_RDWR, 0600);
	if (output_fd >= 0) {
		close(output_fd);
		git_path_buf(&path, "%s", auml_nfd);
		precomposed_unicode = access(path.buf, R_OK) ? 0 : 1;
		git_config_set("core.precomposeunicode", precomposed_unicode ? "true" : "false");
		git_path_buf(&path, "%s", auml_nfc);
		if (unlink(path.buf))
			die_errno(_("failed to unlink '%s'"), path.buf);
	}
	strbuf_release(&path);
}


void precompose_argv(int argc, const char **argv)
{
	int i = 0;
