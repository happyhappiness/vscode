static int tbl_init(void) {
  if (0 == tables_num)
    return 0;

  plugin_register_read("table", tbl_read);
  plugin_register_shutdown("table", tbl_shutdown);
  return 0;
}