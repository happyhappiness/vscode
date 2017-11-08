int create_directory_path(char *fname)
{
	char *p;
	int ret = 0;

	while (*fname == '/')
		fname++;
	while (strncmp(fname, "./", 2) == 0)
		fname += 2;

	umask(orig_umask);
	p = fname;
	while ((p = strchr(p,'/')) != NULL) {
		*p = '\0';
		if (do_mkdir(fname, ACCESSPERMS) < 0 && errno != EEXIST)
		    ret = -1;
		*p++ = '/';
	}
	umask(0);

	return ret;
}