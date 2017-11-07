static const char *get_pwd_cwd(void)
{
	static char cwd[PATH_MAX + 1];
	char *pwd;
	struct stat cwd_stat, pwd_stat;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return NULL;
	pwd = getenv("PWD");
	if (pwd && strcmp(pwd, cwd)) {
		stat(cwd, &cwd_stat);
		if ((cwd_stat.st_dev || cwd_stat.st_ino) &&
		    !stat(pwd, &pwd_stat) &&
		    pwd_stat.st_dev == cwd_stat.st_dev &&
		    pwd_stat.st_ino == cwd_stat.st_ino) {
			strlcpy(cwd, pwd, PATH_MAX);
		}
	}
	return cwd;
}