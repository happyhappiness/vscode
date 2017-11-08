static char *uid_to_name(uid_t uid)
{
	struct passwd *pass = getpwuid(uid);
	if (pass) return(pass->pw_name);
	return NULL;
}