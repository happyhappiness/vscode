static void send_directory(int f,struct file_list *flist,char *dir)
{
	DIR *d;
	struct dirent *di;
	char fname[MAXPATHLEN];
	int l;
	char *p;

	d = opendir(dir);
	if (!d) {
		io_error = 1;
		fprintf(FERROR,"%s: %s\n",
			dir,strerror(errno));
		return;
	}

	strncpy(fname,dir,MAXPATHLEN-1);
	fname[MAXPATHLEN-1]=0;
	l = strlen(fname);
	if (fname[l-1] != '/') {
		if (l == MAXPATHLEN-1) {
			io_error = 1;
			fprintf(FERROR,"skipping long-named directory %s\n",fname);
			closedir(d);
			return;
		}
		strcat(fname,"/");
		l++;
	}
	p = fname + strlen(fname);

	if (cvs_exclude) {
		if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN-1) {
			strcpy(p,".cvsignore");
			local_exclude_list = make_exclude_list(fname,NULL,0);
		} else {
			io_error = 1;
			fprintf(FINFO,"cannot cvs-exclude in long-named directory %s\n",fname);
		}
	}  
	
	for (di=readdir(d); di; di=readdir(d)) {
		if (strcmp(di->d_name,".")==0 ||
		    strcmp(di->d_name,"..")==0)
			continue;
		strncpy(p,di->d_name,MAXPATHLEN-(l+1));
		send_file_name(f,flist,fname,recurse,FLAG_DELETE);
	}

	closedir(d);
}