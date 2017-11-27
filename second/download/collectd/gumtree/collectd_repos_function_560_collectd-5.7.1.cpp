static int ascent_account_player(player_stats_t *ps, /* {{{ */
                                 player_info_t *pi) {
  if (pi->race >= 0) {
    if (((size_t)pi->race >= RACES_LIST_LENGTH) ||
        (races_list[pi->race] == NULL))
      ERROR("ascent plugin: Ignoring invalid numeric race %i.", pi->race);
    else
      ps->races[pi->race]++;
  }

  if (pi->class >= 0) {
    if (((size_t)pi->class >= CLASSES_LIST_LENGTH) ||
        (classes_list[pi->class] == NULL))
      ERROR("ascent plugin: Ignoring invalid numeric class %i.", pi->class);
    else
      ps->classes[pi->class]++;
  }

  if (pi->gender >= 0) {
    if (((size_t)pi->gender >= GENDERS_LIST_LENGTH) ||
        (genders_list[pi->gender] == NULL))
      ERROR("ascent plugin: Ignoring invalid numeric gender %i.", pi->gender);
    else
      ps->genders[pi->gender]++;
  }

  if (pi->level > 0) {
    ps->level_sum += pi->level;
    ps->level_num++;
  }

  if (pi->latency >= 0) {
    ps->latency_sum += pi->latency;
    ps->latency_num++;
  }

  return (0);
}