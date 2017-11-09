char *uid_to_user(uid_t uid)
{
	struct passwd *pass = getpwuid(uid);
	if (pass)
		return strdup(pass->pw_name);
	return NULL;
}