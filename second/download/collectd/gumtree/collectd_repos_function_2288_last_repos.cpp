static int ctail_init(void) {
  char str[255];

  if (tail_match_list_num == 0) {
    WARNING("tail plugin: File list is empty. Returning an error.");
    return -1;
  }

  for (size_t i = 0; i < tail_match_list_num; i++) {
    snprintf(str, sizeof(str), "tail-%zu", i);

    plugin_register_complex_read(NULL, str, ctail_read,
                                 tail_match_list_intervals[i],
                                 &(user_data_t){
                                     .data = tail_match_list[i],
                                 });
  }

  return 0;
}