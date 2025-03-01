static int get_tmpname(char *fnametmp, char *fname)
{
	char *f;

	/* open tmp file */
	if (tmpdir) {
		f = strrchr(fname,'/');
		if (f == NULL) 
			f = fname;
		else 
			f++;
		if (strlen(tmpdir)+strlen(f)+10 > MAXPATHLEN) {
			rprintf(FERROR,"filename too long\n");
			return 0;
		}
		snprintf(fnametmp,MAXPATHLEN, "%s/.%s.XXXXXX",tmpdir,f);
		return 1;
	} 

	f = strrchr(fname,'/');

	if (strlen(fname)+9 > MAXPATHLEN) {
		rprintf(FERROR,"filename too long\n");
		return 0;
	}

	if (f) {
		*f = 0;
		snprintf(fnametmp,MAXPATHLEN,"%s/.%s.XXXXXX",
			 fname,f+1);
		*f = '/';
	} else {
		snprintf(fnametmp,MAXPATHLEN,".%s.XXXXXX",fname);
	}

	return 1;
}