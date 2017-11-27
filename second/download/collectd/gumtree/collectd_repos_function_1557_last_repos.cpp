static void tbl_setup(tbl_t *tbl, char *file) {
  tbl->file = sstrdup(file);
  tbl->sep = NULL;
  tbl->plugin_name = NULL;
  tbl->instance = NULL;

  tbl->results = NULL;
  tbl->results_num = 0;

  tbl->max_colnum = 0;
}