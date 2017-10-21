	if (!flist->files) out_of_memory("send_file_list");

	for (i=0;i<argc;i++) {
		char fname2[MAXPATHLEN];
		char *fname = fname2;

		strncpy(fname,argv[i],MAXPATHLEN-1);
		fname[MAXPATHLEN-1] = 0;

		l = strlen(fname);
		if (l != 1 && fname[l-1] == '/') {
			strcat(fname,".");
		}

		if (link_stat(fname,&st) != 0) {
			io_error=1;
			fprintf(FERROR,"%s : %s\n",fname,strerror(errno));
			continue;
		}

		if (S_ISDIR(st.st_mode) && !recurse) {
			fprintf(FINFO,"skipping directory %s\n",fname);
			continue;
		}

		dir = NULL;

		if (!relative_paths) {
