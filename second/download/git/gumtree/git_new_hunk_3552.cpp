 free_specs:
	for (i = 0; i < nr_spec; i++)
		free(specs[i]);
	free(specs);
}

int cmd_main(int argc, const char **argv)
{
	struct strbuf buf = STRBUF_INIT;
	int nongit;

	setup_git_directory_gently(&nongit);
	if (argc < 2) {
		error("remote-curl: usage: git remote-curl <remote> [<url>]");
		return 1;
	}

