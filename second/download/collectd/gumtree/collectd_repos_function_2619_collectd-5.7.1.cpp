static oconfig_item_t *cf_read_dir(const char *dir, const char *pattern,
                                   int depth) {
  oconfig_item_t *root = NULL;
  DIR *dh;
  struct dirent *de;
  char **filenames = NULL;
  int filenames_num = 0;
  int status;

  assert(depth < CF_MAX_DEPTH);

  dh = opendir(dir);
  if (dh == NULL) {
    char errbuf[1024];
    ERROR("configfile: opendir failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (NULL);
  }

  root = calloc(1, sizeof(*root));
  if (root == NULL) {
    ERROR("configfile: calloc failed.");
    closedir(dh);
    return (NULL);
  }

  while ((de = readdir(dh)) != NULL) {
    char name[1024];
    char **tmp;

    if ((de->d_name[0] == '.') || (de->d_name[0] == 0))
      continue;

    status = ssnprintf(name, sizeof(name), "%s/%s", dir, de->d_name);
    if ((status < 0) || ((size_t)status >= sizeof(name))) {
      ERROR("configfile: Not including `%s/%s' because its"
            " name is too long.",
            dir, de->d_name);
      closedir(dh);
      for (int i = 0; i < filenames_num; ++i)
        free(filenames[i]);
      free(filenames);
      free(root);
      return (NULL);
    }

    ++filenames_num;
    tmp = realloc(filenames, filenames_num * sizeof(*filenames));
    if (tmp == NULL) {
      ERROR("configfile: realloc failed.");
      closedir(dh);
      for (int i = 0; i < filenames_num - 1; ++i)
        free(filenames[i]);
      free(filenames);
      free(root);
      return (NULL);
    }
    filenames = tmp;

    filenames[filenames_num - 1] = sstrdup(name);
  }

  if (filenames == NULL) {
    closedir(dh);
    return (root);
  }

  qsort((void *)filenames, filenames_num, sizeof(*filenames),
        cf_compare_string);

  for (int i = 0; i < filenames_num; ++i) {
    oconfig_item_t *temp;
    char *name = filenames[i];

    temp = cf_read_generic(name, pattern, depth);
    if (temp == NULL) {
      /* An error should already have been reported. */
      sfree(name);
      continue;
    }

    cf_ci_append_children(root, temp);
    sfree(temp->children);
    sfree(temp);

    free(name);
  }

  closedir(dh);
  free(filenames);
  return (root);
}