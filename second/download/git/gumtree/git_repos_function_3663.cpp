static int valid_remote_nick(const char *name)
{
	if (!name[0] || is_dot_or_dotdot(name))
		return 0;
	return !strchr(name, '/'); /* no slash */
}