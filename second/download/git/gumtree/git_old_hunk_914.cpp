
static const char *open_pack_file(const char *pack_name)
{
	if (from_stdin) {
		input_fd = 0;
		if (!pack_name) {
			static char tmp_file[PATH_MAX];
			output_fd = odb_mkstemp(tmp_file, sizeof(tmp_file),
						"pack/tmp_pack_XXXXXX");
			pack_name = xstrdup(tmp_file);
		} else
			output_fd = open(pack_name, O_CREAT|O_EXCL|O_RDWR, 0600);
		if (output_fd < 0)
			die_errno(_("unable to create '%s'"), pack_name);
		nothread_data.pack_fd = output_fd;
	} else {
		input_fd = open(pack_name, O_RDONLY);
		if (input_fd < 0)
			die_errno(_("cannot open packfile '%s'"), pack_name);
		output_fd = -1;
