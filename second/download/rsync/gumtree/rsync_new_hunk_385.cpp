
	if (!name) {
		fprintf(FERROR,"out of memory in delete_already_done");
		exit_cleanup(1);
	}

	name[strlen(name)-2] = 0;

	p = strrchr(name,'/');
	if (!p) {
		free(name);
		return 0;
	}
	*p = 0;

	strcat(name,"/.");

	while (low != high) {
		int mid = (low+high)/2;
		int ret = strcmp(f_name(flist->files[flist_up(flist, mid)]),name);
		if (ret == 0) {
			free(name);
			return 1;
