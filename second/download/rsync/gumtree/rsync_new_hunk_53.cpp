
  if (S_ISDIR(st.st_mode) && !recurse) {
    fprintf(stderr,"skipping directory %s\n",fname);
    return NULL;
  }

  if (one_file_system && st.st_dev != filesystem_dev)
    return NULL;

  if (!match_file_name(fname,&st))
    return NULL;

  if (verbose > 2)
    fprintf(stderr,"make_file(%s)\n",fname);

