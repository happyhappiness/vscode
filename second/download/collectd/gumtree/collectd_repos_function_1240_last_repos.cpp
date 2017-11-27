static int read_hugepage_entry(const char *path, const char *entry,
                               void *e_info) {
  char path2[PATH_MAX];
  struct entry_info *info = e_info;
  double value;

  snprintf(path2, sizeof(path2), "%s/%s", path, entry);

  FILE *fh = fopen(path2, "rt");
  if (fh == NULL) {
    ERROR("%s: cannot open %s", g_plugin_name, path2);
    return -1;
  }

  if (fscanf(fh, "%lf", &value) != 1) {
    ERROR("%s: cannot parse file %s", g_plugin_name, path2);
    fclose(fh);
    return -1;
  }
  fclose(fh);

  if (strcmp(entry, "nr_hugepages") == 0) {
    info->nr = value;
    info->flags |= HP_HAVE_NR;
  } else if (strcmp(entry, "surplus_hugepages") == 0) {
    info->surplus = value;
    info->flags |= HP_HAVE_SURPLUS;
  } else if (strcmp(entry, "free_hugepages") == 0) {
    info->free = value;
    info->flags |= HP_HAVE_FREE;
  }

  if (info->flags != HP_HAVE_ALL) {
    return 0;
  }

  submit_hp(info);

  /* Reset flags so subsequent calls don't submit again. */
  info->flags = 0;
  return 0;
}