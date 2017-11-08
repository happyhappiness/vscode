static uid_t name_to_uid(char *name)
{
	struct passwd *pass;
	if (!name || !*name) return 0;
	pass = getpwnam(name);
	if (pass) return(pass->pw_uid);
	return 0;
}