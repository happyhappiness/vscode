int user_to_uid(const char *name, uid_t *uid_p, BOOL num_ok)
{
	struct passwd *pass;
	if (!name || !*name)
		return 0;
	if (num_ok && name[strspn(name, "0123456789")] == '\0') {
		*uid_p = id_parse(name);
		return 1;
	}
	if (!(pass = getpwnam(name)))
		return 0;
	*uid_p = pass->pw_uid;
	return 1;
}