static oconfig_item_t *cf_read_generic(const char *path, const char *pattern,
                                       int depth) {
  oconfig_item_t *root = NULL;
  int status;
  const char *path_ptr;
  wordexp_t we;

  if (depth >= CF_MAX_DEPTH) {
    ERROR("configfile: Not including `%s' because the maximum "
          "nesting depth has been reached.",
          path);
    return (NULL);
  }

  status = wordexp(path, &we, WRDE_NOCMD);
  if (status != 0) {
    ERROR("configfile: wordexp (%s) failed.", path);
    return (NULL);
  }

  root = calloc(1, sizeof(*root));
  if (root == NULL) {
    ERROR("configfile: calloc failed.");
    return (NULL);
  }

  /* wordexp() might return a sorted list already. That's not
   * documented though, so let's make sure we get what we want. */
  qsort((void *)we.we_wordv, we.we_wordc, sizeof(*we.we_wordv),
        cf_compare_string);

  for (size_t i = 0; i < we.we_wordc; i++) {
    oconfig_item_t *temp;
    struct stat statbuf;

    path_ptr = we.we_wordv[i];

    status = stat(path_ptr, &statbuf);
    if (status != 0) {
      char errbuf[1024];
      WARNING("configfile: stat (%s) failed: %s", path_ptr,
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    if (S_ISREG(statbuf.st_mode))
      temp = cf_read_file(path_ptr, pattern, depth);
    else if (S_ISDIR(statbuf.st_mode))
      temp = cf_read_dir(path_ptr, pattern, depth);
    else {
      WARNING("configfile: %s is neither a file nor a "
              "directory.",
              path);
      continue;
    }

    if (temp == NULL) {
      oconfig_free(root);
      return (NULL);
    }

    cf_ci_append_children(root, temp);
    sfree(temp->children);
    sfree(temp);
  }

  wordfree(&we);

  return (root);
}