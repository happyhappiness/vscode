		absorb_git_dir_into_superproject(prefix,
				list.entries[i]->name, flags);

	return 0;
}

#define SUPPORT_SUPER_PREFIX (1<<0)

struct cmd_struct {
	const char *cmd;
	int (*fn)(int, const char **, const char *);
	unsigned option;
