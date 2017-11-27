static void slaves_free_all (mb_slave_t *slaves, size_t slaves_num) /* {{{ */
{
  if (slaves == NULL)
    return;

  for (size_t i = 0; i < slaves_num; i++)
    data_free_all (slaves[i].collect);
  sfree (slaves);
}