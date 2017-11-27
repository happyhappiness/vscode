static int o_read(void) /* {{{ */
{
  size_t i;

  for (i = 0; i < databases_num; i++)
    o_read_database(databases[i]);

  return 0;
}