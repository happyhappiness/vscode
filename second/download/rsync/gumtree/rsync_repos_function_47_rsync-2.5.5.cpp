void add_cvs_excludes(void)
{
	char fname[MAXPATHLEN];
	char *p;
	int i;
  
	for (i=0; cvs_ignore_list[i]; i++)
		add_exclude(cvs_ignore_list[i], 0);

	if ((p=getenv("HOME")) && strlen(p) < (MAXPATHLEN-12)) {
		snprintf(fname,sizeof(fname), "%s/.cvsignore",p);
		add_exclude_file(fname,0,0);
	}

	add_exclude_line(getenv("CVSIGNORE"));
}