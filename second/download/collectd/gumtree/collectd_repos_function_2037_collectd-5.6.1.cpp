static int ctail_init (void)
{
  char str[255];

  if (tail_match_list_num == 0)
  {
    WARNING ("tail plugin: File list is empty. Returning an error.");
    return (-1);
  }

  for (size_t i = 0; i < tail_match_list_num; i++)
  {
    ssnprintf(str, sizeof(str), "tail-%zu", i);

    user_data_t ud = {
     .data = tail_match_list[i]
    };

    plugin_register_complex_read (NULL, str, ctail_read, tail_match_list_intervals[i], &ud);
  }

  return (0);
}