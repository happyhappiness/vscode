static int tbl_finish(tbl_t *tbl) {
  for (size_t i = 0; i < tbl->results_num; ++i)
    tbl->results[i].ds = NULL;
  return 0;
}