static void tbl_result_setup(tbl_result_t *res) {
  res->type = NULL;

  res->instance_prefix = NULL;
  res->instances = NULL;
  res->instances_num = 0;

  res->values = NULL;
  res->values_num = 0;

  res->ds = NULL;
}