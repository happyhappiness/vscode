	git_config_get_string("imap.pass", &server.pass);
	git_config_get_int("imap.port", &server.port);
	git_config_get_string("imap.tunnel", &server.tunnel);
	git_config_get_string("imap.authmethod", &server.auth_method);
}

int main(int argc, char **argv)
{
	struct strbuf all_msgs = STRBUF_INIT;
	struct strbuf msg = STRBUF_INIT;
	struct imap_store *ctx = NULL;
	int ofs = 0;
	int r;
	int total, n = 0;
	int nongit_ok;

	git_extract_argv0_path(argv[0]);

	git_setup_gettext();

	if (argc != 1)
		usage(imap_send_usage);

	setup_git_directory_gently(&nongit_ok);
	git_imap_config();

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!server.folder) {
		fprintf(stderr, "no imap store specified\n");
		return 1;
