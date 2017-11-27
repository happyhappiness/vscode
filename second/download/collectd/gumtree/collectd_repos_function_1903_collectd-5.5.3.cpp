static int ctail_init (void)
{
  struct timespec cb_interval;
  char str[255];
  user_data_t ud;
  size_t i;

  if (tail_match_list_num == 0)
  {
    WARNING ("tail plugin: File list is empty. Returning an error.");
    return (-1);
  }

  memset(&ud, '\0', sizeof(ud));

  for (i = 0; i < tail_match_list_num; i++)
  {
    ud.data = (void *)tail_match_list[i];
    ssnprintf(str, sizeof(str), "tail-%zu", i);
    CDTIME_T_TO_TIMESPEC (tail_match_list_intervals[i], &cb_interval);
    plugin_register_complex_read (NULL, str, ctail_read, &cb_interval, &ud);
  }

  return (0);
}