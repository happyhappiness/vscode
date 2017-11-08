static void glob_match(char *arg, int abpos, int fbpos)
{
	int len;
	char *slash;

	while (*arg == '.' && arg[1] == '/') {
		if (fbpos < 0) {
			ENSURE_MEMSPACE(glob.filt_buf, char, glob.fbsize, glob.absize);
			memcpy(glob.filt_buf, glob.arg_buf, abpos + 1);
			fbpos = abpos;
		}
		ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, abpos + 3);
		glob.arg_buf[abpos++] = *arg++;
		glob.arg_buf[abpos++] = *arg++;
		glob.arg_buf[abpos] = '\0';
	}
	if ((slash = strchr(arg, '/')) != NULL) {
		*slash = '\0';
		len = slash - arg;
	} else
		len = strlen(arg);
	if (strpbrk(arg, "*?[")) {
		struct dirent *di;
		DIR *d;

		if (!(d = opendir(abpos ? glob.arg_buf : ".")))
			return;
		while ((di = readdir(d)) != NULL) {
			char *dname = d_name(di);
			if (dname[0] == '.' && (dname[1] == '\0'
			  || (dname[1] == '.' && dname[2] == '\0')))
				continue;
			if (!wildmatch(arg, dname))
				continue;
			call_glob_match(dname, strlen(dname), 1,
					slash ? arg + len + 1 : NULL,
					abpos, fbpos);
		}
		closedir(d);
	} else {
		call_glob_match(arg, len, 0,
				slash ? arg + len + 1 : NULL,
				abpos, fbpos);
	}
	if (slash)
		*slash = '/';
}