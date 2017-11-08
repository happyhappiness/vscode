struct exclude_struct **make_exclude_list(const char *fname,
					  struct exclude_struct **list1,
					  int fatal, int include)
{
	struct exclude_struct **list=list1;
	FILE *f = fopen(fname,"r");
	char line[MAXPATHLEN];
	if (!f) {
		if (fatal) {
			rsyserr(FERROR, errno,
                                "failed to open %s file %s",
                                include ? "include" : "exclude",
                                fname);
			exit_cleanup(RERR_FILEIO);
		}
		return list;
	}

	while (fgets(line,MAXPATHLEN,f)) {
		int l = strlen(line);
		if (l && line[l-1] == '\n') l--;
		line[l] = 0;
		if (line[0] && (line[0] != ';') && (line[0] != '#')) {
			/* Skip lines starting with semicolon or pound.
			   It probably wouldn't cause any harm to not skip
			     them but there's no need to save them. */
			add_exclude_list(line,&list,include);
		}
	}
	fclose(f);
	return list;
}