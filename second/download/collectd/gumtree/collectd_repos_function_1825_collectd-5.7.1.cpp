cu_match_t *
match_create_callback(const char *regex, const char *excluderegex,
                      int (*callback)(const char *str, char *const *matches,
                                      size_t matches_num, void *user_data),
                      void *user_data,
                      void (*free_user_data)(void *user_data)) {
  cu_match_t *obj;
  int status;

  DEBUG("utils_match: match_create_callback: regex = %s, excluderegex = %s",
        regex, excluderegex);

  obj = calloc(1, sizeof(*obj));
  if (obj == NULL)
    return (NULL);

  status = regcomp(&obj->regex, regex, REG_EXTENDED | REG_NEWLINE);
  if (status != 0) {
    ERROR("Compiling the regular expression \"%s\" failed.", regex);
    sfree(obj);
    return (NULL);
  }

  if (excluderegex && strcmp(excluderegex, "") != 0) {
    status = regcomp(&obj->excluderegex, excluderegex, REG_EXTENDED);
    if (status != 0) {
      ERROR("Compiling the excluding regular expression \"%s\" failed.",
            excluderegex);
      sfree(obj);
      return (NULL);
    }
    obj->flags |= UTILS_MATCH_FLAGS_EXCLUDE_REGEX;
  }

  obj->callback = callback;
  obj->user_data = user_data;
  obj->free = free_user_data;

  return (obj);
}