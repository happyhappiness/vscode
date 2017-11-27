static int entropy_read(void) {
  value_t v;
  if (parse_value_file(ENTROPY_FILE, &v, DS_TYPE_GAUGE) != 0) {
    ERROR("entropy plugin: Reading \"" ENTROPY_FILE "\" failed.");
    return -1;
  }

  entropy_submit(v);
  return 0;
}