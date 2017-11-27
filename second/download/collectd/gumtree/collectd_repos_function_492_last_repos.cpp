static int ascent_submit_players(player_stats_t *ps) /* {{{ */
{
  gauge_t value;

  for (size_t i = 0; i < RACES_LIST_LENGTH; i++)
    if (races_list[i] != NULL)
      ascent_submit_gauge("by-race", "players", races_list[i],
                          (gauge_t)ps->races[i]);

  for (size_t i = 0; i < CLASSES_LIST_LENGTH; i++)
    if (classes_list[i] != NULL)
      ascent_submit_gauge("by-class", "players", classes_list[i],
                          (gauge_t)ps->classes[i]);

  for (size_t i = 0; i < GENDERS_LIST_LENGTH; i++)
    if (genders_list[i] != NULL)
      ascent_submit_gauge("by-gender", "players", genders_list[i],
                          (gauge_t)ps->genders[i]);

  if (ps->level_num <= 0)
    value = NAN;
  else
    value = ((double)ps->level_sum) / ((double)ps->level_num);
  ascent_submit_gauge(NULL, "gauge", "avg-level", value);

  /* Latency is in ms, but we store seconds. */
  if (ps->latency_num <= 0)
    value = NAN;
  else
    value = ((double)ps->latency_sum) / (1000.0 * ((double)ps->latency_num));
  ascent_submit_gauge(NULL, "latency", "average", value);

  return 0;
}