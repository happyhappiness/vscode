void match_destroy(cu_match_t *obj) {
  if (obj == NULL)
    return;

  if (obj->flags & UTILS_MATCH_FLAGS_FREE_USER_DATA)
    sfree(obj->user_data);
  if (obj->flags & UTILS_MATCH_FLAGS_REGEX)
    regfree(&obj->regex);
  if (obj->flags & UTILS_MATCH_FLAGS_EXCLUDE_REGEX)
    regfree(&obj->excluderegex);

  sfree(obj);
}