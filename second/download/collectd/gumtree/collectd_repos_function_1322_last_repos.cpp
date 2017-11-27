static bool ident_matches(const value_list_t *vl, const value_list_t *matcher) {
  if (fnmatch(matcher->host, vl->host, 0))
    return false;

  if (fnmatch(matcher->plugin, vl->plugin, 0))
    return false;
  if (fnmatch(matcher->plugin_instance, vl->plugin_instance, 0))
    return false;

  if (fnmatch(matcher->type, vl->type, 0))
    return false;
  if (fnmatch(matcher->type_instance, vl->type_instance, 0))
    return false;

  return true;
}