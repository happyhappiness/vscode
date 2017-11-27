static int mh_config_match(const oconfig_item_t *ci, /* {{{ */
                           mh_match_t *m) {
  mh_hash_match_t *tmp;

  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_NUMBER) ||
      (ci->values[1].type != OCONFIG_TYPE_NUMBER)) {
    ERROR("hashed match: The `Match' option requires "
          "exactly two numeric arguments.");
    return -1;
  }

  if ((ci->values[0].value.number < 0) || (ci->values[1].value.number < 0)) {
    ERROR("hashed match: The arguments of the `Match' "
          "option must be positive.");
    return -1;
  }

  tmp = realloc(m->matches, sizeof(*tmp) * (m->matches_num + 1));
  if (tmp == NULL) {
    ERROR("hashed match: realloc failed.");
    return -1;
  }
  m->matches = tmp;
  tmp = m->matches + m->matches_num;

  tmp->match = (uint32_t)(ci->values[0].value.number + .5);
  tmp->total = (uint32_t)(ci->values[1].value.number + .5);

  if (tmp->match >= tmp->total) {
    ERROR("hashed match: The first argument of the `Match' option "
          "must be smaller than the second argument.");
    return -1;
  }
  assert(tmp->total != 0);

  m->matches_num++;
  return 0;
}