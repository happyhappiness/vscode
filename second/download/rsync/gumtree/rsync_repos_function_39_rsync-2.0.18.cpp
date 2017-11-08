struct exclude_struct **make_exclude_list(char *fname,
					  struct exclude_struct **list1,
					  int fatal, int include)
{
	struct exclude_struct **list=list1;
	FILE *f = fopen(fname,"r");
	char line[MAXPATHLEN];
	if (!f) {
		if (fatal) {
			rprintf(FERROR,"%s : %s\n",fname,strerror(errno));
			exit_cleanup(1);
		}
		return list;
	}

	while (fgets(line,MAXPATHLEN,f)) {
		int l = strlen(line);
		if (l && line[l-1] == '\n') l--;
		line[l] = 0;
		if (line[0]) add_exclude_list(line,&list,include);
	}
	fclose(f);
	return list;
}