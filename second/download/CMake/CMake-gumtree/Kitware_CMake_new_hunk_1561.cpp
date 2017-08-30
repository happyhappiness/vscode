#endif
    if (i == -1)
      return -1;
    if (i >= TAR_MAXPATHLEN)
      i = TAR_MAXPATHLEN - 1;
    path[i] = '\0';
#ifdef DEBUG
    printf("    tar_append_file(): encoding symlink \"%s\" -> "