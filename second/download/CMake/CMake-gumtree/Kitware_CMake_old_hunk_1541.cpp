#ifdef DEBUG
    puts("    tar_extract_all(): calling th_get_pathname()");
#endif
    filename = th_get_pathname(t);
    if (t->options & TAR_VERBOSE)
      th_print_long_ls(t);
    if (prefix != NULL)
      snprintf(buf, sizeof(buf), "%s/%s", prefix, filename);
    else
      strlcpy(buf, filename, sizeof(buf));
#ifdef DEBUG
    printf("    tar_extract_all(): calling tar_extract_file(t, "
           "\"%s\")\n", buf);
#endif
    if (tar_extract_file(t, buf) != 0)
      return -1;
  }