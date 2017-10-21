  int updated = 0;
  struct stat st2;

  if (dry_run) return 0;

  if (!st) {
    if (lstat(fname,&st2) != 0) {
      fprintf(FERROR,"stat %s : %s\n",fname,strerror(errno));
      return 0;
    }
    st = &st2;
  }

