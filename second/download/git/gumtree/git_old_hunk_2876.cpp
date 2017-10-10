	}
	argv[argc] = NULL;

	return set_remote_branches(argv[0], argv + 1, add_mode);
}

static int set_url(int argc, const char **argv)
{
	int i, push_mode = 0, add_mode = 0, delete_mode = 0;
	int matches = 0, negative_matches = 0;
	const char *remotename = NULL;
	const char *newurl = NULL;
