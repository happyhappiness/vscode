    l = strlen(fname);
    if (l != 1 && fname[l-1] == '/') {
      strcat(fname,".");
    }

    if (lstat(fname,&st) != 0) {
      fprintf(stderr,"%s : %s\n",fname,strerror(errno));
      continue;
    }

    if (S_ISDIR(st.st_mode) && !recurse) {
      fprintf(stderr,"skipping directory %s\n",fname);
      continue;
    }

    dir = NULL;
    p = strrchr(fname,'/');
    if (p) {
