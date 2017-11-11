int create_directory_path(char *fname, int base_umask)
{
	char *p;

	while (*fname == '/')
		fname++;
	while (strncmp(fname, "./", 2) == 0)
		fname += 2;

	p = fname;
	while ((p = strchr(p,'/')) != NULL) {
		*p = 0;
		do_mkdir(fname, 0777 & ~base_umask);
		*p = '/';
		p++;
	}
	return 0;
}