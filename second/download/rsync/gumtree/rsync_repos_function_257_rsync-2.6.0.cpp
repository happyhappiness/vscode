static char *getpassf(char *filename)
{
	char buffer[100];
	int fd=0;
	STRUCT_STAT st;
	int ok = 1;
	extern int am_root;
	char *envpw=getenv("RSYNC_PASSWORD");

	if (!filename) return NULL;

	if ( (fd=open(filename,O_RDONLY)) == -1) {
		rsyserr(FERROR, errno, "could not open password file \"%s\"",filename);
		if (envpw) rprintf(FERROR,"falling back to RSYNC_PASSWORD environment variable.\n");	
		return NULL;
	}
	
	if (do_stat(filename, &st) == -1) {
		rsyserr(FERROR, errno, "stat(%s)", filename);
		ok = 0;
	} else if ((st.st_mode & 06) != 0) {
		rprintf(FERROR,"password file must not be other-accessible\n");
		ok = 0;
	} else if (am_root && (st.st_uid != 0)) {
		rprintf(FERROR,"password file must be owned by root when running as root\n");
		ok = 0;
	}
	if (!ok) {
		rprintf(FERROR,"continuing without password file\n");
		if (envpw) rprintf(FERROR,"using RSYNC_PASSWORD environment variable.\n");
		close(fd);
		return NULL;
	}

	if (envpw) rprintf(FERROR,"RSYNC_PASSWORD environment variable ignored\n");

	buffer[sizeof(buffer)-1]='\0';
	if (read(fd,buffer,sizeof(buffer)-1) > 0)
	{
		char *p = strtok(buffer,"\n\r");
		close(fd);
		if (p) p = strdup(p);
		return p;
	}	

	return NULL;
}