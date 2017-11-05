int main(int argc, char **argv)
{
	char *method = getenv("REQUEST_METHOD");
	char *dir;
	struct service_cmd *cmd = NULL;
	char *cmd_arg = NULL;
	int i;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);
	set_die_routine(die_webcgi);
	set_die_is_recursing_routine(die_webcgi_recursing);

	if (!method)
		die("No REQUEST_METHOD from server");
	if (!strcmp(method, "HEAD"))
		method = "GET";
	dir = getdir();

	for (i = 0; i < ARRAY_SIZE(services); i++) {
		struct service_cmd *c = &services[i];
		regex_t re;
		regmatch_t out[1];

		if (regcomp(&re, c->pattern, REG_EXTENDED))
			die("Bogus regex in service table: %s", c->pattern);
		if (!regexec(&re, dir, 1, out, 0)) {
			size_t n;

			if (strcmp(method, c->method)) {
				const char *proto = getenv("SERVER_PROTOCOL");
				if (proto && !strcmp(proto, "HTTP/1.1")) {
					http_status(405, "Method Not Allowed");
					hdr_str("Allow", !strcmp(c->method, "GET") ?
						"GET, HEAD" : c->method);
				} else
					http_status(400, "Bad Request");
				hdr_nocache();
				end_headers();
				return 0;
			}

			cmd = c;
			n = out[0].rm_eo - out[0].rm_so;
			cmd_arg = xmemdupz(dir + out[0].rm_so + 1, n - 1);
			dir[out[0].rm_so] = 0;
			break;
		}
		regfree(&re);
	}

	if (!cmd)
		not_found("Request not supported: '%s'", dir);

	setup_path();
	if (!enter_repo(dir, 0))
		not_found("Not a git repository: '%s'", dir);
	if (!getenv("GIT_HTTP_EXPORT_ALL") &&
	    access("git-daemon-export-ok", F_OK) )
		not_found("Repository not exported: '%s'", dir);

	http_config();
	max_request_buffer = git_env_ulong("GIT_HTTP_MAX_REQUEST_BUFFER",
					   max_request_buffer);

	cmd->imp(cmd_arg);
	return 0;
}