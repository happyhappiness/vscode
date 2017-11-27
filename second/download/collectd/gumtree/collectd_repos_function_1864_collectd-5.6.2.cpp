static void data_free_one(mb_data_t *data) /* {{{ */
{
  if (data == NULL)
    return;

  sfree(data->name);
  sfree(data);
}