static oconfig_item_t *cf_read_file(const char *file, const char *pattern,
                                    int depth) {
  oconfig_item_t *root;
  int status;

  assert(depth < CF_MAX_DEPTH);

  if (pattern != NULL) {
#if HAVE_FNMATCH_H && HAVE_LIBGEN_H
    char *tmp = sstrdup(file);
    char *filename = basename(tmp);

    if ((filename != NULL) && (fnmatch(pattern, filename, 0) != 0)) {
      DEBUG("configfile: Not including `%s' because it "
            "does not match pattern `%s'.",
            filename, pattern);
      free(tmp);
      return NULL;
    }

    free(tmp);
#else
    ERROR("configfile: Cannot apply pattern filter '%s' "
          "to file '%s': functions basename() and / or "
          "fnmatch() not available.",
          pattern, file);
#endif /* HAVE_FNMATCH_H && HAVE_LIBGEN_H */
  }

  root = oconfig_parse_file(file);
  if (root == NULL) {
    ERROR("configfile: Cannot read file `%s'.", file);
    return NULL;
  }

  status = cf_include_all(root, depth);
  if (status != 0) {
    oconfig_free(root);
    return NULL;
  }

  return root;
}