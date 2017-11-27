static void slaves_free_all (mb_slave_t *slaves, size_t slaves_num) /* {{{ */
{
  size_t i;

  if (slaves == NULL)
    return;

  for (i = 0; i < slaves_num; i++)
    data_free_all (slaves[i].collect);
  sfree (slaves);
}