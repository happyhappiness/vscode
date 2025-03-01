	{"GET", "/objects/pack/pack-[0-9a-f]{40}\\.idx$", get_idx_file},

	{"POST", "/git-upload-pack$", service_rpc},
	{"POST", "/git-receive-pack$", service_rpc}
};

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
