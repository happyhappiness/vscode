void match_destroy(cu_match_t *obj) {
  if (obj == NULL)
    return;

  if (obj->flags & UTILS_MATCH_FLAGS_REGEX)
    regfree(&obj->regex);
  if (obj->flags & UTILS_MATCH_FLAGS_EXCLUDE_REGEX)
    regfree(&obj->excluderegex);
  if ((obj->user_data != NULL) && (obj->free != NULL))
    (*obj->free)(obj->user_data);

  sfree(obj);
}