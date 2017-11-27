static char *match_substr(const char *str, int begin, int end) {
  char *ret;
  size_t ret_len;

  if ((begin < 0) || (end < 0) || (begin >= end))
    return NULL;
  if ((size_t)end > (strlen(str) + 1)) {
    ERROR("utils_match: match_substr: `end' points after end of string.");
    return NULL;
  }

  ret_len = end - begin;
  ret = malloc(ret_len + 1);
  if (ret == NULL) {
    ERROR("utils_match: match_substr: malloc failed.");
    return NULL;
  }

  sstrncpy(ret, str + begin, ret_len + 1);
  return ret;
}