static int mb_shutdown(void) /* {{{ */
{
  data_free_all(data_definitions);
  data_definitions = NULL;

  return 0;
}