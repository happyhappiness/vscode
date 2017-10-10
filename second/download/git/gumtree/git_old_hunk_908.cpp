static void report_pack_garbage(unsigned seen_bits, const char *path)
{
	if (seen_bits == PACKDIR_FILE_IDX)
		string_list_append(&pack_garbage, path);
}

static void git_config_date_string(const char *key, const char **output)
{
	if (git_config_get_string_const(key, output))
		return;
	if (strcmp(*output, "now")) {
		unsigned long now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
}

static void process_log_file(void)
{
	struct stat st;
	if (fstat(get_lock_file_fd(&log_lock), &st)) {
		/*
		 * Perhaps there was an i/o error or another
