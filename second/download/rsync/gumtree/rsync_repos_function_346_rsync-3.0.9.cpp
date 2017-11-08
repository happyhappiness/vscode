int name_to_uid(const char *name, uid_t *uid_p)
{
	struct passwd *pass;
	if (!name || !*name)
		return 0;
	if (!(pass = getpwnam(name)))
		return 0;
	*uid_p = pass->pw_uid;
	return 1;
}