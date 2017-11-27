static int tbl_parse_line(tbl_t *tbl, char *line, size_t len) {
  char *fields[tbl->max_colnum + 1];
  char *ptr, *saveptr;

  size_t i = 0;

  ptr = line;
  saveptr = NULL;
  while (NULL != (fields[i] = strtok_r(ptr, tbl->sep, &saveptr))) {
    ptr = NULL;
    ++i;

    if (i > tbl->max_colnum)
      break;
  }

  if (i <= tbl->max_colnum) {
    log_warn("Not enough columns in line "
             "(expected at least %zu, got %zu).",
             tbl->max_colnum + 1, i);
    return -1;
  }

  for (i = 0; i < tbl->results_num; ++i)
    if (0 != tbl_result_dispatch(tbl, tbl->results + i, fields,
                                 STATIC_ARRAY_SIZE(fields))) {
      log_err("Failed to dispatch result.");
      continue;
    }
  return 0;
}