#endif
    if (i == -1)
      return -1;
    if (i >= MAXPATHLEN)
      i = MAXPATHLEN - 1;
    path[i] = '\0';
#ifdef DEBUG
    printf("    tar_append_file(): encoding symlink \"%s\" -> "