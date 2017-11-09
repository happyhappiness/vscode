static int valid_remote_nick(const char *name)
{
	if (!name[0] || is_dot_or_dotdot(name))
		return 0;

	/* remote nicknames cannot contain slashes */
	while (*name)
		if (is_dir_sep(*name++))
			return 0;
	return 1;
}