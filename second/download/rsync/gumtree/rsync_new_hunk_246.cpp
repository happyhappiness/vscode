    if (S_ISDIR(st.st_mode) && !recurse) {
      fprintf(FERROR,"skipping directory %s\n",fname);
      continue;
    }

    dir = NULL;

    if (!relative_paths) {
	    p = strrchr(fname,'/');
	    if (p) {
		    *p = 0;
		    if (p == fname) 
			    dir = "/";
		    else
			    dir = fname;      
		    fname = p+1;      
	    }
    }

    if (!*fname)
      fname = ".";

    if (dir && *dir) {
      if (getcwd(dbuf,MAXPATHLEN-1) == NULL) {
	fprintf(FERROR,"getwd : %s\n",strerror(errno));
