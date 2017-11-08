void add_cvs_excludes(void)
{
	char fname[MAXPATHLEN];
	char *p;
	int i;

	for (i=0; cvs_ignore_list[i]; i++)
		add_exclude(&exclude_list, cvs_ignore_list[i], ADD_EXCLUDE);

	if ((p=getenv("HOME")) && strlen(p) < (MAXPATHLEN-12)) {
		snprintf(fname,sizeof(fname), "%s/.cvsignore",p);
		add_exclude_file(&exclude_list,fname,MISSING_OK,ADD_EXCLUDE);
	}

	add_exclude_line(&exclude_list, getenv("CVSIGNORE"), ADD_EXCLUDE);
}