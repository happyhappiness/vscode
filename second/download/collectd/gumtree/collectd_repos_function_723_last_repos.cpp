static int cow_shutdown(void) {
  OW_finish();
  ignorelist_free(sensor_list);

  direct_list_free();

  if (regex_direct_initialized) {
    regfree(&regex_direct);
  }

  return 0;
}