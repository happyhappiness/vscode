static int count_cruft(const char *basename, const char *path, void *data)
{
	loose_garbage(path);
	return 0;
}

static char const * const count_objects_usage[] = {
	N_("git count-objects [-v] [-H | --human-readable]"),
	NULL
};

int cmd_count_objects(int argc, const char **argv, const char *prefix)
